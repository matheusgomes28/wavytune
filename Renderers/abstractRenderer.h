#ifndef RENDERERS_ABSTRACT_RENDERER_H
#define RENDERERS_ABSTRACT_RENDERER_H
#include <vector>
#include <map>

class ShaderProgram;
class DrawBuffer;
class Entity;
class VAO;
class VBO;


//! TODO : Problem! May have different types of data to
//! render in a single render. Possible solutions are:

//!  - Inheritance: Make render type which contains renderers
//!    as instances, each renderer will deal with a type of data.
//!    Disadvantage is to make a different data for each type.

//!  - Use of different shaders and enums to figure out what 
//!    type of data to render. Disadvantage is that the renderer
//!    representation would have to be changed.




//! Class that defines the interface of a render.
//! Note that all the renderes in this program 
//! will inherit from this class, hence try and
//! keep it fairly tidy.
class AbstractRenderer
{
public:
	AbstractRenderer();
	virtual ~AbstractRenderer();
	
	virtual void render() = 0;
	virtual void sendGPUData() = 0;
	virtual void createGPUBuffers() = 0;
	void addEntityData(Entity*, DrawBuffer* data) = 0;
	
	void setShaderProgram(ShaderProgram* program);
};
#endif
