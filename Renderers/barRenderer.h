#ifndef RENDERERS_BAR_RENDERER_H
#define RENDERERS_BAR_RENDERER_H
#include "abstractRenderer.h"


class BarRenderer : AbstractRenderer
{
public:
	BarRenderer();
	~BarRenderer();

	void render() override;
	void createGPUBuffers() override;
	void sendGPUData() override;

};
#endif