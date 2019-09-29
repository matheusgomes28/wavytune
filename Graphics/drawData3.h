#ifndef GRAPHICS_DRAW_DATA_3
#define GRAPHICS_DRAW_DATA_3
#include "stdafx.h"
#include "abstractDrawData.h"

class DrawData3 : public AbstractDrawData<glm::vec3>
{
public:
	DrawData3();

	const DrawVector& getData() const override;
	void setData(const DrawVector& data) override;
};
#endif
