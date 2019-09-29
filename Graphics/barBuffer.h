#ifndef GRAPHICS_BAR_BUFFER_H
#define GRAPHICS_BAR_BUFFER_H
#include "stdafx.h"
#include "drawBuffer.h"

//! Maybe this should be put near where it's
//! actually used. TODO
class BarBuffer : public DrawBuffer
{
public:
	BarBuffer();
	BarBuffer(const float& width);

	glm::mat4 getTransform() const override;
	
private:
	void setUp() override;

	float height_;
	float width_;
};
#endif