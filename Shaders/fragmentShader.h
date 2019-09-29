#pragma once
#include "abstractShader.h"

class FragmentShader : public AbstractShader
{
public:
	FragmentShader(const std::string& path) : AbstractShader(path)
	{}

	int getGlEnum() const override
	{
		return GL_FRAGMENT_SHADER;
	}
};
