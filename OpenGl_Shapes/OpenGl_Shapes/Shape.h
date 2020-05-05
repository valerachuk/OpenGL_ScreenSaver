#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <deque>
#include <string>
#include <functional>
#include "Buffer.h"
#include "BoundingBox.h"
#include "RenderSystem.h"

class Shape {
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

	std::deque<glm::vec2> _trail;

	BoundingBox calcBoundingBox() const;
	glm::mat4 calcShapeMatrix(const glm::vec2&);
	glm::mat4 calcShapeMatrix();
	void fillTrail();
	void drawTrail();

	friend class PathRecorder;
	friend class Memento;

public:
	std::shared_ptr<Buffer> _buffer;
	void setScale(const glm::vec2&);
	void setPos(const glm::vec2&);
	const glm::vec2& getPos() const;
	void setColor(const glm::vec4&);
	void setTrail(bool);
	void setDeformed(bool);
	void setHidden(bool);

	void translate(const glm::vec2&);
	void clampCanvasFit();

	bool isIntersects(Shape& component) const;

	void draw();

	void print(std::ostream& stream, std::string indent = "") const;

	explicit Shape(std::shared_ptr<Buffer>);
	Shape();

};