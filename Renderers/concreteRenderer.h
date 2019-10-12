#ifndef RENDERERS_CONCRETE_RENDERER_h
#define RENDERERS_CONCRETE_RENDERER_h
#include "abstractRenderer.h"
#include <map>


class VAO;
class VBO;
class Entity;
class DrawBuffer;
class ShaderProgram;
class ConcreteRenderer : AbstractRenderer
{
	using EntityDataMap = std::map<Entity*, std::vector<DrawBuffer*>>;

public:
	ConcreteRenderer();
	~ConcreteRenderer();
	

	//! overrides
	
	
protected:
	EntityDataMap entityData_;
	std::vector<VAO*> vaos_;
	std::vector<VBO*> vbos_;
	ShaderProgram* shaderProgram_;
};
#endif