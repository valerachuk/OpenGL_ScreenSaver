#pragma once
#include "BoundingBox.h"
#include "glm/glm.hpp"
#include <string>

class IDrawable {
public:
	virtual void draw() = 0;
};

class IRigidBody {
public:
	virtual BoundingBox calcBoundingBox() const = 0;
	virtual void translate(const glm::vec2&) = 0;
	virtual void clampCanvasFit() = 0;
};

class INameable {
public:
	//virtual const std::string& getName() const = 0;
	//virtual void setName(const std::string&) = 0;
};

class ICanvasComponent : public IDrawable, public IRigidBody, public INameable { };

