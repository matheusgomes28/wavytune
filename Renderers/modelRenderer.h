//! TODO : Rename this to something which makes more sense
//! The idea of this renderer is that it deals with different
//! types of drawing data. I.e. textured and non-textured data.
#ifndef RENDERERS_MODEL_RENDERER_H
#define RENDERERS_MODEL_RENDERER_H

#include "abstractRenderer.h"
#include <map>

enum class BufferType {TEXTURED, NON_TEXTURED};

class ModelRenderer : AbstractRenderer
{
public:
	ModelRenderer();


private:
	std::map<BufferType, AbstractRenderer*> renderers_;

};
#endif