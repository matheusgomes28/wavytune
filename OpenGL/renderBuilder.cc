#include "renderBuilder.h"
#include "Renderers/barRenderer.h"
#include "GLAbstractions/vao.h"
#include "GLAbstractions/vbo.h"
#include "GLAbstractions/vertexAttribute.h"
#include "Graphics/drawData3.h"
#include "Graphics/colourdata.h"
#include "Graphics/drawBuffer.h"

AbstractRenderer* RenderBuilder::buildBarRenderer() const
{
	BarRenderer* rendererPtr = new BarRenderer();
	DrawBuffer* barbuffer = new DrawBuffer();
	
	DrawData3* vertices = new DrawData3;
	vertices->setData({
		{0, 0, 0},
		{0, 1, 0},
		{1, 1, 0},
		{0, 0, 0},
		{1, 1, 0},
		{1, 0, 0}
	});
	barbuffer->setVertices(vertices);

	DrawData3* normals = new DrawData3;
	normals->setData({
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1}
	});
	barbuffer->setNormals(normals);

	ColourData* colours = new ColourData;
	colours->setData({
		{255, 0, 0, 1},
		{255, 0, 0, 1},
		{255, 0, 0, 1},
		{255, 0, 0, 1},
		{255, 0, 0, 1},
		{255, 0, 0, 1}
	});
	barbuffer->setColours(colours);


	


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
