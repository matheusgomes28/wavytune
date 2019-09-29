#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>

// TODO : Make sure this is all done correctly with inheritance
// and abstraction.
class TextReader;
class AbstractShader
{
	public:
		AbstractShader(const std::string& path);
		AbstractShader(const AbstractShader& fromCopy);
		AbstractShader(AbstractShader&& fromMover);
		~AbstractShader();

		void compile();
		unsigned int getAddress() const;
		std::string getCompileMessage() const;

		AbstractShader& operator=(const AbstractShader& fromcopy);
		AbstractShader&& operator=(AbstractShader&& fromMove);


	private:
		std::string path;
		unsigned int address;
		TextReader* reader;

		unsigned int generateBuffer() const;
		std::string loadShaderData() const;
		virtual int getGlEnum() const = 0;

};
