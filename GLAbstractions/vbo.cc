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

void VBO::addData(const std::vector<glm::vec4>& data) const
{
	if (isValid()) {
		glBindBuffer(GL_ARRAY_BUFFER, getId());

		const unsigned VECTOR_SIZE = data.size();
		const unsigned ELEMENT_SIZE = sizeof(glm::vec4);
		glBufferData(GL_ARRAY_BUFFER, VECTOR_SIZE * ELEMENT_SIZE, &data[0], GL_STATIC_DRAW);
	}
}

void VBO::addData(const std::vector<glm::vec3>& data) const
{
	if (isValid()) {
		glBindBuffer(GL_ARRAY_BUFFER, getId());

		const unsigned VECTOR_SIZE = data.size();
		const unsigned ELEMENT_SIZE = sizeof(glm::vec3);
		glBufferData(GL_ARRAY_BUFFER, VECTOR_SIZE * ELEMENT_SIZE, &data[0], GL_STATIC_DRAW);
	}
}

void VBO::addData(const std::vector<glm::vec2>& data) const
{
	if (isValid()) {
		glBindBuffer(GL_ARRAY_BUFFER, getId());

		const unsigned VECTOR_SIZE = data.size();
		const unsigned ELEMENT_SIZE = sizeof(glm::vec2);
		glBufferData(GL_ARRAY_BUFFER, VECTOR_SIZE * ELEMENT_SIZE, &data[0], GL_STATIC_DRAW);
	}
}

void VBO::addData(const std::vector<unsigned>& data) const
{
	if (isValid()) {
		glBindBuffer(GL_ARRAY_BUFFER, getId());

		const unsigned VECTOR_SIZE = data.size();
		const unsigned ELEMENT_SIZE = sizeof(unsigned);
		glBufferData(GL_ARRAY_BUFFER, VECTOR_SIZE * ELEMENT_SIZE, &data[0], GL_STATIC_DRAW);
	}
}

