#pragma once
#include "GLRenderSystem.h"

class IDrawable {
	virtual void Draw(GLRenderSystem&) = 0;
};