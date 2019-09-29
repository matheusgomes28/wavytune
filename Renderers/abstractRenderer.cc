#include "stdafx.h"
#include "abstractRenderer.h"
#include "Shaders/shaderProgram.h"
#include "GLAbstractions/vao.h"

AbstractRenderer::AbstractRenderer()
{
}

AbstractRenderer::~AbstractRenderer()
{
	// ShaderProgram delete
	if (shaderProgram_) {
		delete shaderProgram_;
		shaderProgram_ = nullptr;
	}

	// Delete the VAOs
	for (VAO* vaoPtr : vaos_) {
		if (vaoPtr) {
			delete vaoPtr;
		}
	}
	vaos_.clear();

	// Delete the VBOs
	for (VBO* vboPtr : vbos_) {
		if (vboPtr) {
			delete vboPtr;
		}
	}
	vbos_.clear();

	// Delete the entity data
	for (auto kvPair : entityData_) {
		if (kvPair.first) {
			delete kvPair.first;
		}
		
		for (DrawBuffer* buffer : kvPair.second) {
			if (buffer) {
				delete buffer;
			}
		}
	}
	entityData_.clear();
}

void AbstractRenderer::addShaderProgram(ShaderProgram* program)
{
	shaderProgram_ = program;
}

void AbstractRenderer::addEntityData(Entity* entity, DrawBuffer* data)
{
	auto find = entityData_.find(entity);

	if (find != end(entityData_)) {
		find->second.push_back(data);
	}
	else {
		entityData_[entity] = { data };
	}
}


