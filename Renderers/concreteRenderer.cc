#include "stdafx.h"
#include "concreteRenderer.h"
#include "GLAbstractions/vao.h"
#include "GLAbstractions/vbo.h"
#include "GLAbstractions/vertexAttribute.h"
#include "Graphics/drawData3.h"
#include "Graphics/drawBuffer.h"
#include "Shaders/shaderProgram.h"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <cmath>

std::vector<std::string> getError()
{
	std::vector<std::string> retVal;
	GLenum error = glGetError();
	while (error = glGetError() != GL_NO_ERROR) {

		switch (error)
		{
		case GL_INVALID_ENUM:
			retVal.push_back("Invalid enum.");
			break;
		case GL_INVALID_VALUE:
			retVal.push_back("Invalid function value.");
			break;
		case GL_INVALID_OPERATION:
			retVal.push_back("Invalid operation.");
			break;
		case GL_STACK_OVERFLOW:
			retVal.push_back("stack overflow.");
			break;
		case GL_STACK_UNDERFLOW:
			retVal.push_back("stack underflow.");
			break;
		case GL_OUT_OF_MEMORY:
			retVal.push_back("Out of memory.");
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			retVal.push_back("Invalid framebuffer operation.");
			break;
		case GL_TABLE_TOO_LARGE:
			retVal.push_back("Table is too large.");
			break;
		}
	}
	return retVal;
}


ConcreteRenderer::ConcreteRenderer()
	: shaderProgram_(nullptr),
	vao_(nullptr),
	pointsToDraw_{ 0 }
{
	setShader();
}

ConcreteRenderer::~ConcreteRenderer()
{
	if (shaderProgram_) {
		delete shaderProgram_;
		shaderProgram_ = nullptr;
	}

	// Delete each vao and clear vec
	if (vao_) delete vao_;

	// Delete the buffers this renderer owns
	for (auto kvPair : vbos_) {
		if (kvPair.second) {
			delete kvPair.second;
		}
	}
	vbos_.clear();

	// Delete the entity data
	for (auto kvPair : entityData_) {
		
		// Delete the entity ptr
		if (kvPair.first) delete kvPair.first;
		
		for (DrawBuffer* buffer : kvPair.second) {
			if (buffer) delete buffer;
		}
	}
	entityData_.clear();
}

void ConcreteRenderer::setShader()
{
	auto errors = getError();
	// Make sure we delete it if its 
	// already created
	if (shaderProgram_) {
		delete shaderProgram_;
		shaderProgram_ = nullptr;
	}

	// TODO : Create the shader objects here
	// TODO : Remove hard-coded path for the shaders
	const std::string VS_PATH = "C:\\Users\\Matheus\\audioVisualiser\\vs.glsl";
	const std::string FS_PATH = "C:\\Users\\Matheus\\audioVisualiser\\fs.glsl";
	shaderProgram_ = new ShaderProgram(VS_PATH, FS_PATH);
	shaderProgram_->compileAndLink();
	errors = getError();
}

ShaderProgram* ConcreteRenderer::getShader() const
{
	return shaderProgram_;
}

void ConcreteRenderer::createGPUBuffers()
{
	auto errors = getError();
	// Make sure these are smart pointers
	vao_ = new VAO{};

	VBO* vertexVBO = new VBO{};
	vbos_.insert({ BUFFER_TYPE::VERTEX, vertexVBO });

	VBO* normalVBO = new VBO{};
	vbos_.insert({ BUFFER_TYPE::NORMAL, normalVBO });
	errors = getError();
}

void ConcreteRenderer::sendGPUData()
{
	pointsToDraw_ = 0;
	getShader()->use();
	glBindVertexArray(vao_->getId());

	// Allocate enough memory at the buffers
	VBO* vertexVBO = vbos_[BUFFER_TYPE::VERTEX];
	vertexVBO->allocateMemory(getVertexMemoryNeeded());
	VBO* normalVBO = vbos_[BUFFER_TYPE::NORMAL];
	normalVBO->allocateMemory(getNormalMemoryNeeded());
	
	// Stores the offset (in bytes) to each buffer for
	// where to start adding the next chunk of data
	unsigned vertexOffset = 0;
	unsigned normalOffset = 0;
	for (auto& kvPair : entityData_) {
		for (DrawBuffer* data : kvPair.second) {
			vertexVBO->addData(data->getVertices().getData(), vertexOffset);
			vertexOffset += data->getVertices().getGPUSize();

			normalVBO->addData(data->getNormals().getData(), normalOffset);
			normalOffset += data->getNormals().getGPUSize();

			// Keep track of how many points to draw
			pointsToDraw_ += data->getVertices().getData().size();
		}


		// TODO : Add the logic for the matrices here
		// for each entity, use SSBOs maybe?
	}

	// Sort out the vertex attributes here
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO->getId());
	VertexAttribute* vertexAttribs = new VertexAttribute;
	vertexAttribs->setOffset(0);
	vertexAttribs->setSize(3);
	vertexAttribs->setNormalised(false);
	vertexAttribs->setStride(0);
	vertexAttribs->setType(VERTEX_TYPE::FLOAT);
	vao_->addBufferConfigs(vertexVBO, vertexAttribs);
	GLint posPtr = glGetAttribLocation(getShader()->getAddress(), "aPos");
	glVertexAttribPointer(
		posPtr,
		vertexAttribs->getSize(),
		(int) vertexAttribs->getType(),
		vertexAttribs->getNormalised(),
		vertexAttribs->getStride(),
		0
	);
	glEnableVertexAttribArray(posPtr);


	glBindBuffer(GL_ARRAY_BUFFER, normalVBO->getId());
	VertexAttribute* normalAttribs = new VertexAttribute;
	normalAttribs->setOffset(0);
	normalAttribs->setSize(3);
	normalAttribs->setNormalised(false);
	normalAttribs->setStride(0);
	normalAttribs->setType(VERTEX_TYPE::FLOAT);
	vao_->addBufferConfigs(normalVBO, normalAttribs);
	GLint norPtr = glGetAttribLocation(getShader()->getAddress(), "aNor");
	glVertexAttribPointer(
		norPtr,
		normalAttribs->getSize(),
		(int)normalAttribs->getType(),
		normalAttribs->getNormalised(),
		normalAttribs->getStride(),
		0
	);
	glEnableVertexAttribArray(norPtr);
	getShader()->unuse();
}

void ConcreteRenderer::render(const glm::mat4& proj, const glm::mat4& view)
{
	auto errors = getError();
	//! TODO : Implement this

	//! The last piece of the puzzle. Problem is to
	//! think about how to link the attributes and
	//! buffers in the VAO. Specifically, where is the
	//! best place to send the information to the GPU?
	//! Would it be here or in the VAO object itself?
	getShader()->use();

	float green = abs(0.6 + sin(glfwGetTime() * 2) / 2.0);
	getShader()->setUniform("green", green);
	getShader()->setUniform("proj", proj);
	getShader()->setUniform("view", view);

	
	// Enable vertices and normals for drawing
	glBindVertexArray(vao_->getId());
	glDrawArrays(GL_TRIANGLES, 0, pointsToDraw_);
	glBindVertexArray(0);

	getShader()->unuse();
	errors = getError();
}


void ConcreteRenderer::addEntityData(Entity* entPtr, DrawBuffer* buffer)
{
	auto found = entityData_.find(entPtr);
	if (found != end(entityData_)) {
		found->second.push_back(buffer);
	}
	else {
		entityData_[entPtr] = { buffer };
	}
}


unsigned ConcreteRenderer::getVertexMemoryNeeded() const
{
	unsigned total = 0;
	for (auto& kvPair : entityData_) {
		for (DrawBuffer* dataPtr : kvPair.second) {
			total += dataPtr->getVertices().getGPUSize();
		}
	}
	return total;
}

unsigned ConcreteRenderer::getNormalMemoryNeeded() const
{
	unsigned total = 0;
	for (auto& kvPair : entityData_) {
		for (DrawBuffer* dataPtr : kvPair.second) {
			total += dataPtr->getNormals().getGPUSize();
		}
	}
	return total;
}
