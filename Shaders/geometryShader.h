#pragma once
#include "abstractShader.h"

class GeometryShader : public AbstractShader
{
public:
	GeometryShader(const std::string& path) : AbstractShader(path)
	{}

	int getGlEnum() const override
	{
		return GL_GEOMETRY_SHADER;
	}
};
