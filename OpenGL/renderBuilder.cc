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
		{0, 0, 0},
		{0.5, 0, 0},
		{0, 0.5, 0},
		{0.5, 0, 0},
		{0.5, 0.5, 0},
		{0, 0.5, 0}
	};
	DrawData3* vertices = new DrawData3();
	vertices->setData(vertArray);
	barBuffer->setVertices(vertices);

	std::vector<glm::vec3> normArray = {
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1}
	};
	DrawData3* normals = new DrawData3();
	normals->setData(normArray);
	barBuffer->setNormals(normals);

	Entity* barTopEntity = new Entity;
	barTopEntity->setName("Bar entity");

	retVal->addEntityData(barTopEntity, barBuffer);
	return retVal;
}
