#pragma once
#include "BoundingBox.h"
#include "glm/glm.hpp"
#include <string>
#include <iostream>

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

class IPrintable {
public:
	virtual void print(std::ostream& stream, std::string indent) const = 0;
};

class Selectable { //
protected:
	int _id;
public:
	virtual Selectable* getById(int id) {
		return id == _id ? this : nullptr;
	}
	void setId(int id) {
		_id = id;
	}
};

class ICanvasComponent : public IDrawable, public IRigidBody, public IPrintable, public Selectable { };

