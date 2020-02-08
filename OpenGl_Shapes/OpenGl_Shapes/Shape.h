#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <functional>
#include "Buffer.h"
#include "Interfaces.h"
#include "BoundingBox.h"
#include "RenderSystem.h"

class Shape: public ICanvasComponent {
private:
	const float DEFORM_FACTOR = 2.0f;
	const float START_OPACITY = 0.4f;
	const float K_OPACITY = 0.05f;

	glm::vec2 _scale;
	glm::vec2 _position;
	glm::vec4 _color;
	float _zIndex;
	bool _isHillighted;
	bool _isDeformed;
	std::shared_ptr<Buffer> _buffer;
	std::vector<Shape> _trail;

	void generateTrail();
	BoundingBox calcBoundingBox() const override;
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
	void clampCanvasFit();

	bool isOtherCollision(const Shape&);
	void draw() override;

	Shape(std::shared_ptr<Buffer>);

};