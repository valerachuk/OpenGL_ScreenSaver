#include "Figure.h"

void Figure::clampPos()
{
	if (getPos().x + getScale().x / 2 > 1)
	{
		_position.x = 1.0f - getScale().x / 2;
	}
}

const glm::vec2& Figure::getScale() const
{
	return _scale;
}

void Figure::setScale(const glm::vec2& scale)
{
	_scale = scale;
}

const glm::vec2& Figure::getPos() const
{
	return _position;
}

void Figure::setPos(const glm::vec2& position)
{
	_position = position;
}

const glm::vec4& Figure::getColor() const
{
	return _color;
}

void Figure::setColor(const glm::vec4& color)
{
	_color = color;
}

const Buffer& Figure::getBuffer() const
{
	return *_buffer;
}

void Figure::setBuffer(std::shared_ptr<Buffer> buffer)
{
	_buffer = buffer;
}

bool Figure::isOtherCollision(const Figure& other)
{
	return (getPos().x + getScale().x / 2 >= other.getPos().x - other.getScale().x / 2 ||
			getPos().x - getScale().x / 2 <= other.getPos().x + other.getScale().x / 2) &&
			(getPos().y + getScale().y / 2 >= other.getPos().y - other.getScale().y / 2 ||
			getPos().y - getScale().y / 2 <= other.getPos().y + other.getScale().y / 2);
}
