#include "stdafx.h"
#include "concreteRenderer.h"


ConcreteRenderer::ConcreteRenderer()
	: shaderProgram_(nullptr)
{
}

ConcreteRenderer::~ConcreteRenderer()
{
	if (shaderProgram_) {
		delete shaderProgram_;
		shaderProgram_ = nullptr;
	}

	// Delete each vao and clear vec
	for (VAO* vaoPtr : vaos_) {
		if (vaoPtr) delete vaoPtr;
	}
	vaos_.clear();

	// Delete each vbo and clear vec
	for (VBO* vboPtr : vbos_) {
		if (vboPtr) delete vboPtr;
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