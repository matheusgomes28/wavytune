#ifndef OPENGL_DRAWABLES_H
#define OPENGL_DRAWABLES_H
#include <vector>

class AbstractRenderer;
class Drawables {
	using RendererPtr = AbstractRenderer*;

public:
	static Drawables* Instance();
	static void Destroy();

	void drawEverything();
	void addRenderer(RendererPtr renderer);


private:
	Drawables();
	~Drawables();
	static Drawables* instance;


	std::vector<RendererPtr> renderers_;
};
#endif 
