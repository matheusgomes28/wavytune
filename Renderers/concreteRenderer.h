#ifndef RENDERERS_CONCRETE_RENDERER_h
#define RENDERERS_CONCRETE_RENDERER_h
#include "abstractRenderer.h"
#include <map>


class VAO;
class VBO;
class Entity;
class DrawBuffer;
class ShaderProgram;

enum class BUFFER_TYPE { VERTEX, NORMAL, TEXTURE };

class ConcreteRenderer : AbstractRenderer
{
	using EntityDataMap = std::map<Entity*, std::vector<DrawBuffer*>>;

public:
	ConcreteRenderer();
	~ConcreteRenderer();

	//! overrides
	void render() override;
	void sendGPUData() override;
	void createGPUBuffers() override;
	void addEntityData(Entity* entPtr, DrawBuffer* dataPtr) override;
	
	
protected:
	EntityDataMap entityData_;
	VAO* vao_;
	std::map<BUFFER_TYPE, VBO*> vbos_;
	ShaderProgram* shaderProgram_;


	void setShader(ShaderProgram* program) override;
	ShaderProgram getShader() override;

private:
	unsigned getVertexMemoryNeeded() const;
	unsigned getNormalMemoryNeeded() const;

};
#endif