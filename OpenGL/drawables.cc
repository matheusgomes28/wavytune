#include "drawables.h"
#include "Renderers/abstractRenderer.h"

Drawables::Drawables()
{
}

Drawables::~Drawables()
{
	for (RendererPtr renderPtr : renderers_) {
		delete renderPtr;
	}
	renderers_.clear();
}

Drawables* Drawables::instance = nullptr;

Drawables* Drawables::Instance()
{
	if (!instance) {
		instance = new Drawables();
	}

	return instance;
}

void Drawables::Destroy()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

void Drawables::drawEverything()
{
	for (RendererPtr renderPtr : renderers_) {
		renderPtr->render();
	}
}

void Drawables::addRenderer(RendererPtr renderer)
{
	renderers_.push_back(renderer);
}