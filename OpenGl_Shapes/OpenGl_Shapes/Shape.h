#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <deque>
#include <string>
#include <functional>
#include "Buffer.h"
#include "Interfaces.h"
#include "BoundingBox.h"
#include "RenderSystem.h"

class Memento;

class Shape: public ICanvasComponent {
private:
	const float DEFORM_FACTOR = 2.0f;
	const float START_OPACITY = 0.1f;
	const float K_OPACITY = 0.005f;

	glm::vec2 _scale;
	glm::vec2 _position;
	glm::vec4 _color;
	bool _isHidden;
	bool _isDeformed;
	bool _hasTrail;
	std::shared_ptr<Buffer> _buffer;
	std::deque<glm::vec2> _trail;

	BoundingBox calcBoundingBox() const override;
	glm::mat4 calcShapeMatrix(const glm::vec2&);
	glm::mat4 calcShapeMatrix();
	void fillTrail();
	void drawTrail();

	friend class Memento;

public:
	void setScale(const glm::vec2&) override;
	void setPos(const glm::vec2&) override;
	void setColor(const glm::vec4&) override;
	void setTrail(bool) override;
	void setDeformed(bool) override;
	void setHidden(bool) override;

	void translate(const glm::vec2&) override;
	void clampCanvasFit() override;

	bool isOtherCollision(const Shape&);
	void draw() override;

	void print(std::ostream& stream, std::string indent = "") const override;

	explicit Shape(std::shared_ptr<Buffer>);

};