#include "renderBuilder.h"
#include "Renderers/barRenderer.h"
#include "GLAbstractions/vao.h"
#include "GLAbstractions/vbo.h"
#include "GLAbstractions/vertexAttribute.h"

AbstractRenderer* RenderBuilder::buildBarRenderer() const
{
	BarRenderer* rendererPtr = new BarRenderer();


	// Set the VAO and that here
	VAO* vaoPtr = new VAO();
	vaoPtr->setName("Bar Renderer VAO.");

	// Set the VBO stuff here
	VBO* vertexVBO = new VBO();
	VBO* normalVBO = new VBO();
	VBO* texelVBO = new VBO();
	
	
	// Set the attribute stuff here
	VertexAttribute* attr = new VertexAttribute();

	// TODO : Finish this simple example

	// Set the entity here (May have nothing in it tho)


	return nullptr;
}
