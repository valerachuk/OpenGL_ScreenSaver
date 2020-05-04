#pragma once
#include "BoundingBox.h"
#include "glm/glm.hpp"
#include <string>
#include <iostream>

class IDrawable {
public:
	virtual ~IDrawable() = default;
	virtual void draw() = 0;
};

class IRigidBody {
public:
	virtual BoundingBox calcBoundingBox() const = 0;
	virtual void translate(const glm::vec2&) = 0;
	virtual void clampCanvasFit() = 0;
	virtual void setScale(const glm::vec2&) = 0;
	virtual void setPos(const glm::vec2&) = 0;
};

class IClonable {
public:
	virtual IClonable* deepClone() const = 0;
};

class IPrintable {
public:
	virtual void print(std::ostream& stream, std::string indent) const = 0;
};

class ISelectable { //boor...
protected:
	int _id = -1;
public:
	virtual ISelectable* getById(int id) {
		return id == _id ? this : nullptr;
	}
	void setId(int id) {
		_id = id;
	}
};

class ICanvasComponent : public IDrawable, public IRigidBody, public IPrintable, public ISelectable, public IClonable {
public:
	virtual void setColor(const glm::vec4&) = 0;
	virtual void setTrail(bool) = 0;
	virtual void setDeformed(bool) = 0;
	virtual void setHidden(bool) = 0;
};

