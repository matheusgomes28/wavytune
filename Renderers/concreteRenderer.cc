#include "stdafx.h"
#include "concreteRenderer.h"
#include "GLAbstractions/vao.h"
#include "GLAbstractions/vbo.h"
#include "GLAbstractions/vertexAttribute.h"
#include "Graphics/drawData3.h"
#include "Graphics/drawBuffer.h"

#include "Shaders/shaderProgram.h"


ConcreteRenderer::ConcreteRenderer()
	: shaderProgram_(nullptr),
	vao_(nullptr)
{
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
}

ShaderProgram* ConcreteRenderer::getShader() const
{
	return shaderProgram_;
}

void ConcreteRenderer::createGPUBuffers()
{
	// Make sure these are smart pointers
	vao_ = new VAO{};

	VBO* vertexVBO = new VBO{};
	vbos_.insert({ BUFFER_TYPE::VERTEX, vertexVBO });

	VBO* normalVBO = new VBO{};
	vbos_.insert({ BUFFER_TYPE::NORMAL, normalVBO });
}

void ConcreteRenderer::sendGPUData()
{
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
		}


		// TODO : Add the logic for the matrices here
		// for each entity, use SSBOs maybe?
	}


	// Sort out the vertex attributes here
	VertexAttribute* vertexAttribs = new VertexAttribute;
	vertexAttribs->setOffset(0);
	vertexAttribs->setSize(3);
	vertexAttribs->setNormalised(false);
	vertexAttribs->setStride(0);
	vertexAttribs->setType(VERTEX_TYPE::FLOAT);
	vao_->addBufferConfigs(vertexVBO, vertexAttribs);
	
	VertexAttribute* normalAttribs = new VertexAttribute;
	normalAttribs->setOffset(0);
	normalAttribs->setSize(3);
	normalAttribs->setNormalised(false);
	normalAttribs->setStride(0);
	normalAttribs->setType(VERTEX_TYPE::FLOAT);
	vao_->addBufferConfigs(normalVBO, normalAttribs);

	
}

void ConcreteRenderer::render()
{
	//! TODO : Implement this

	//! The last piece of the puzzle. Problem is to
	//! think about how to link the attributes and
	//! buffers in the VAO. Specifically, where is the
	//! best place to send the information to the GPU?
	//! Would it be here or in the VAO object itself?
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
