/*
#include "stdafx.h"
#include "barBuffer.h"
#include "drawData2.h"
#include "drawData3.h"
#include <glm/gtx/transform.hpp>

BarBuffer::BarBuffer()
	: DrawBuffer("Frequency Bar Buffer"),
	width_(0.2),
	height_(1)
{
	setUp();
}

BarBuffer::BarBuffer(const float& width)
	: DrawBuffer("Frequency Bar Buffer"),
	width_(width),
	height_(1)
{
	setUp();
}

glm::mat4 BarBuffer::getTransform() const
{
	return glm::scale(glm::mat4{ 1 }, { 1, height_, 1 });
}

void BarBuffer::setUp() 
{
	auto vertices = new DrawData3;
	vertices->setData({
		{0, 0, 0},
		{0, 1, 0},
		{1, 0, 0},
		{0, 1, 0},
		{1, 1, 0},
		{1, 0, 0}
     });


	auto normals = new DrawData3;
	normals->setData({
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
	});

	auto texels = new DrawData2;
	texels->setData({
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
		{0, 0},
	});


	setVertices(vertices);
	setNormals(normals);
	setTexels(texels);
}
*/