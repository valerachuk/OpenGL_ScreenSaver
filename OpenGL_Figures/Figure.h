#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "Buffer.h"

class Figure {
private:
	glm::vec2 _scale;
	glm::vec2 _position;
	glm::vec4 _color;
	std::shared_ptr<Buffer> _buffer;
	
	void clampPos();

public:
	const glm::vec2& getScale() const;
	void setScale(const glm::vec2&);

	const glm::vec2& getPos() const;
	void setPos(const glm::vec2&);

	const glm::vec4& getColor() const;
	void setColor(const glm::vec4&);

	const Buffer& getBuffer() const;
	void setBuffer(std::shared_ptr<Buffer> buffer);

	bool isOtherCollision(const Figure&);

};