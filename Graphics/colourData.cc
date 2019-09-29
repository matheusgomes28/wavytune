#include "stdafx.h"
#include "colourData.h"

auto ColourData::getData() const -> const DrawVector&
{
	return data_;
}

void ColourData::setData(const DrawVector& data)
{
	data_ = data;
}