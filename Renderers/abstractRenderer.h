#ifndef RENDERERS_ABSTRACT_RENDERER_H
#define RENDERERS_ABSTRACT_RENDERER_H
#include <vector>
#include <map>

class ShaderProgram;
class DrawBuffer;
class Entity;
class VAO;
class VBO;

//! Class that defines the interface of a render.
//! Note that all the renderes in this program 
//! will inherit from this class, hence try and
//! keep it fairly tidy.
class AbstractRenderer
{
	using EntityDataMap = std::map<Entity*, std::vector<DrawBuffer*>>;
public:
	AbstractRenderer();
	virtual ~AbstractRenderer();
	
	virtual void render() = 0;
	virtual void sendGPUData() = 0;
	virtual void createGPUBuffers() = 0;
	
	void addShaderProgram(ShaderProgram* program);
	void addEntityData(Entity*, DrawBuffer* data);
	

protected:
	//! Note that we will own these pointers!
	std::vector<VAO*> vaos_;
	std::vector<VBO*> vbos_;
	ShaderProgram* shaderProgram_;
	EntityDataMap entityData_;
	
};
#endif
