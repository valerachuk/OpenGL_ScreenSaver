#include "Figure.h"

void Figure::clampPos()
{
	if (getPos().x + getScale().x / 2 > 1)
	{
		_position.x = 1.0f - getScale().x / 2;
	}
}

glm::mat4 Figure::calcModelMatrix()
{
	glm::mat4 matrix(1.0f);
	matrix = glm::scale(matrix, glm::vec3(getScale(), 1.0f));
	matrix = glm::translate(matrix, glm::vec3(getPos(), 0.0f));
	return matrix;
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

bool Figure::getHilighted() const
{
	return _isHillighted;
}

void Figure::setHilighed(bool state)
{
	_isHillighted = state;
}

bool Figure::getDeformed() const
{
	return _isDeformed;
}

void Figure::setDeformed(bool state)
{
	if (state && !_isDeformed)
		_scale *= DEFORM_FACTOR;
	else if (!state && _isDeformed)
		_scale /= DEFORM_FACTOR;

	_isDeformed = state;
}

const Buffer& Figure::getBuffer() const
{
	return *_buffer;
}

void Figure::translate(const glm::vec2& offset)
{
	_position += offset;
	clampPos();
}

bool Figure::isOtherCollision(const Figure& other)
{
	return (getPos().x + getScale().x / 2 >= other.getPos().x - other.getScale().x / 2 ||
			getPos().x - getScale().x / 2 <= other.getPos().x + other.getScale().x / 2) &&
			(getPos().y + getScale().y / 2 >= other.getPos().y - other.getScale().y / 2 ||
			getPos().y - getScale().y / 2 <= other.getPos().y + other.getScale().y / 2);
}

Figure::Figure(std::shared_ptr<Buffer> buffer) :
	_scale(glm::vec2(1.0f)),
	_position(glm::vec2(1.0f)),
	_color(glm::vec4(0.0f)),
	_isHillighted(false),
	_isDeformed(false)
{

}
