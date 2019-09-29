#pragma once
#include "abstractShader.h"

class VertexShader : public AbstractShader
{
public:
	VertexShader(const std::string& path) : AbstractShader(path)
	{}

	// Only function to override
	int getGlEnum() const override
	{
		return GL_VERTEX_SHADER;
	}
};