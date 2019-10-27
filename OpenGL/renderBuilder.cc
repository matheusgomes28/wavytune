#include "renderBuilder.h"
#include "GLAbstractions/vao.h"
#include "GLAbstractions/vbo.h"
#include "GLAbstractions/vertexAttribute.h"
#include "Graphics/drawData3.h"
#include "Graphics/colourdata.h"
#include "Graphics/drawBuffer.h"
#include "Graphics/entity.h"
#include "Renderers/abstractRenderer.h"
#include "Renderers/concreteRenderer.h"

AbstractRenderer* RenderBuilder::buildBarRenderer()
{
	ConcreteRenderer* retVal = new ConcreteRenderer();

	// Create the entity needed and the data needed

	DrawBuffer* barBuffer = new DrawBuffer;
	
	std::vector<glm::vec3> vertArray = {

		// Plane 1
		{-0.5, -0.5, -0.5},
		{ 0.5, -0.5, -0.5},
		{-0.5,  0.5, -0.5},
		{ 0.5, -0.5, -0.5},
		{ 0.5,  0.5, -0.5},
		{-0.5,  0.5, -0.5},

		// Plane 2
		{-0.5, -0.5,  0.5},
		{ 0.5, -0.5,  0.5},
		{-0.5,  0.5,  0.5},
		{ 0.5, -0.5,  0.5},
		{ 0.5,  0.5,  0.5},
		{-0.5,  0.5,  0.5},


		// Plane 3
		{-0.5, -0.5, -0.5},
		{-0.5, -0.5,  0.5},
		{-0.5,  0.5, -0.5},
		{-0.5, -0.5,  0.5},
		{-0.5,  0.5,  0.5},
		{-0.5,  0.5, -0.5},


		// Plane 4
		{ 0.5, -0.5, -0.5},
		{ 0.5, -0.5,  0.5},
		{ 0.5,  0.5, -0.5},
		{ 0.5, -0.5,  0.5},
		{ 0.5,  0.5,  0.5},
		{ 0.5,  0.5, -0.5},

		// Plane 5
		{-0.5,  0.5, -0.5},
		{ 0.5,  0.5, -0.5},
		{-0.5,  0.5,  0.5},
		{-0.5,  0.5,  0.5},
		{ 0.5,  0.5, -0.5},
		{ 0.5,  0.5,  0.5},

		// Plane 6
		{-0.5, -0.5, -0.5},
		{ 0.5, -0.5, -0.5},
		{-0.5, -0.5,  0.5},
		{-0.5, -0.5,  0.5},
		{ 0.5, -0.5, -0.5},
		{ 0.5, -0.5,  0.5}
	};
	DrawData3* vertices = new DrawData3();
	vertices->setData(vertArray);
	barBuffer->setVertices(vertices);

	std::vector<glm::vec3> normArray = {
		// Plane 1
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},

		// Plane 2
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},

		// Plane 3
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},

		// Plane 4
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},

		// Plane 5
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},

		// Plane 6
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
	};
	DrawData3* normals = new DrawData3();
	normals->setData(normArray);
	barBuffer->setNormals(normals);

	std::vector<glm::vec4> colourArray{
		// Plane 1
		{0, 1, 0, 1},
		{0, 1, 0, 1},
		{0, 1, 0, 1},
		{0, 1, 0, 1},
		{0, 1, 0, 1},
		{0, 1, 0, 1},

		// Plane 2
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{1, 0, 0, 1},

		// Plane 3
		{0, 0, 1, 1},
		{0, 0, 1, 1},
		{0, 0, 1, 1},
		{0, 0, 1, 1},
		{0, 0, 1, 1},
		{0, 0, 1, 1},

		// Plane 4
		{0, 1, 0, 1},
		{0, 1, 0, 1},
		{0, 1, 0, 1},
		{0, 1, 0, 1},
		{0, 1, 0, 1},
		{0, 1, 0, 1},

		// Plane 5
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{1, 0, 0, 1},

		// Plane 6
		{0, 0, 1, 1},
		{0, 0, 1, 1},
		{0, 0, 1, 1},
		{0, 0, 1, 1},
		{0, 0, 1, 1},
		{0, 0, 1, 1}
	};
	ColourData* colours = new ColourData();
	colours->setData(colourArray);
	barBuffer->setColours(colours);


	Entity* barTopEntity = new Entity;
	barTopEntity->setName("Bar entity");

	retVal->addEntityData(barTopEntity, barBuffer);
	return retVal;
}
