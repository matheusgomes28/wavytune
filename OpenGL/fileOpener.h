#pragma once
#include <string>
#include <fstream>

class FileOpener
{

public:
	FileOpener();
	FileOpener(std::string path);
	~FileOpener();

private:
	std::string path;
	std::ifstream* inStream;
};
