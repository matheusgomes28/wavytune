#include "stdafx.h"
#include <GL/glew.h>
#include "vbo.h"

VBO::VBO()
	: AbstractIdObject()
{
	generateId();
}

VBO::VBO(const std::string& name)
	: AbstractIdObject(name)
{
	generateId();
}

void VBO::generateId()
{
	GLuint newBuf;
	glGenBuffers(1, &newBuf);
	setId(newBuf);
}

void VBO::allocateMemory(const unsigned& size) const
{
	if (isValid()) {
		glBindBuffer(GL_ARRAY_BUFFER, getId());
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
	}
}

void VBO::addData(const void* data, const unsigned& size, const unsigned& offset) const
{
	if (isValid()) {
		glBindBuffer(GL_ARRAY_BUFFER, getId());
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}
}