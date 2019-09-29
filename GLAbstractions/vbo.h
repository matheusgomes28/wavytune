#ifndef GLABSTRACTIONS_VBO_H
#define GLABSTRACTIONS_VBO_H

#include <string>
#include <vector>
#include "abstractIdObject.h"
class VBO : public AbstractIdObject
{
public:
	VBO();
	VBO(const std::string& name);

	void addData(const std::vector<glm::vec4>& data) const;
	void addData(const std::vector<glm::vec3>& data) const;
	void addData(const std::vector<glm::vec2>& data) const;
	void addData(const std::vector<unsigned>& data) const;

private:
	void generateId() override;
};
#endif