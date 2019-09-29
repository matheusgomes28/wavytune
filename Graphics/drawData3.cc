#include "stdafx.h"
#include "drawData3.h"

DrawData3::DrawData3()
{
}

auto DrawData3::getData() const -> const DrawVector&
{
	return data_;
}

void DrawData3::setData(const DrawVector& data)
{
	data_ = data;
}