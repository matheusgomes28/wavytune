#include "stdafx.h"
#include "concreteRenderer.h"
#include "GLAbstractions/vao.h"
#include "GLAbstractions/vbo.h"
#include "GLAbstractions/vertexAttribute.h"
#include "Graphics/drawData3.h"
#include "Graphics/drawBuffer.h"


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

	// Delete each vbo and clear vec
	// TODO : Make sure the VBOs are properly
	// deleted here
	/*
	for (VBO* vboPtr : vbos_) {
		if (vboPtr) delete vboPtr;
	}
	vbos_.clear();
	*/

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

void ConcreteRenderer::createGPUBuffers()
{
	// Make sure these are smart pointers
	vao_ = new VAO{};

	VBO* vertexVBO = new VBO{};
	vbos_.insert({ BUFFER_TYPE::VERTEX, vertexVBO });

	VBO* normalVBO = new VBO{};
	vbos_.insert({ BUFFER_TYPE::NORMAL, normalVBO });

	VBO* texelVBO = new VBO{};
	vbos_.insert({ BUFFER_TYPE::TEXTURE, texelVBO });
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
		// for each entity
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
