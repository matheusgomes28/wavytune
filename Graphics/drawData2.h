#ifndef GRAPHICS_DRAW_DATA_2
#define GRAPHICS_DRAW_DATA_2
#include "stdafx.h"
#include "abstractDrawData.h"

class DrawData2 : public AbstractDrawData<glm::vec2>
{
public:
	DrawData2();

	const DrawVector& getData() const override;
	void setData(const DrawVector& data) override;
};
#endif
