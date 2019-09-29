#ifndef OPENGL_RENDER_BUILDER_H
#define OPENGL_RENDER_BUILDER_H

class AbstractRenderer;
class RenderBuilder
{
public:	
	AbstractRenderer* buildBarRenderer() const;


	/*
	AbstractRenderer* buildOtherRenderer();
	*/
};
#endif