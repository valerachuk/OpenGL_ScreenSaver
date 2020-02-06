#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "Buffer.h"
#include "IDrawable.h"

class Shape: public IDrawable {
private:
	const int DEFORM_FACTOR = 2;
	const float START_OPACITY = 0.4;
	const float K_OPACITY = 0.05;

	glm::vec2 _scale;
	glm::vec2 _position;
	glm::vec4 _color;
	float _zIndex;
	bool _isHillighted;
	bool _isDeformed;
	std::shared_ptr<Buffer> _buffer;
	std::vector<Shape> _trail;

	void generateTrail();
	void clampPos();
	glm::mat4 calcShapeMatrix();


public:
	void setScale(const glm::vec2&);
	void setPos(const glm::vec2&);
	void setColor(const glm::vec4&);
	void setTrail(bool);
	void setZIndex(float);

	bool getHilighted() const;
	void setHilighed(bool);

	bool getDeformed() const;
	void setDeformed(bool);

	void translate(const glm::vec2&);
	bool isOtherCollision(const Shape&);
	void draw() override;

	Shape(std::shared_ptr<Buffer>);

};