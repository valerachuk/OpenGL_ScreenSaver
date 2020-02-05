#include "Shape.h"

void Shape::clampPos()
{
	if (getPos().x + getScale().x / 2 > 1)
	{
		_position.x = 1.0f - getScale().x / 2;
	}
}

glm::mat4 Shape::calcShapeMatrix()
{
	glm::mat4 matrix(1.0f);
	matrix = glm::scale(matrix, glm::vec3(getScale(), 1.0f));
	matrix = glm::translate(matrix, glm::vec3(getPos(), 0.0f));
	return matrix;
}

const glm::vec2& Shape::getScale() const
{
	return _scale;
}

void Shape::setScale(const glm::vec2& scale)
{
	_scale = scale;
}

const glm::vec2& Shape::getPos() const
{
	return _position;
}

void Shape::setPos(const glm::vec2& position)
{
	_position = position;
}

const glm::vec4& Shape::getColor() const
{
	return _color;
}

void Shape::setColor(const glm::vec4& color)
{
	_color = color;
}

bool Shape::getHilighted() const
{
	return _isHillighted;
}

void Shape::setHilighed(bool state)
{
	_isHillighted = state;
}

bool Shape::getDeformed() const
{
	return _isDeformed;
}

void Shape::setDeformed(bool state)
{
	if (state && !_isDeformed)
		_scale *= DEFORM_FACTOR;
	else if (!state && _isDeformed)
		_scale /= DEFORM_FACTOR;

	_isDeformed = state;
}

const Buffer& Shape::getBuffer() const
{
	return *_buffer;
}

void Shape::translate(const glm::vec2& offset)
{
	setPos(getPos() + offset);
	clampPos();
}

bool Shape::isOtherCollision(const Shape& other)
{
	return (getPos().x + getScale().x / 2 >= other.getPos().x - other.getScale().x / 2 ||
			getPos().x - getScale().x / 2 <= other.getPos().x + other.getScale().x / 2) &&
			(getPos().y + getScale().y / 2 >= other.getPos().y - other.getScale().y / 2 ||
			getPos().y - getScale().y / 2 <= other.getPos().y + other.getScale().y / 2);
}

void Shape::draw()
{
	RenderSystem::getInstance().setShapeTransform(calcShapeMatrix());
	RenderSystem::getInstance().setColor(getColor());
	RenderSystem::getInstance().render(getBuffer().getVAO(), getBuffer().getVertexCount());
}

Shape::Shape(std::shared_ptr<Buffer> buffer) :
	_scale(glm::vec2(1.0f)),
	_position(glm::vec2(1.0f)),
	_color(glm::vec4(0.0f)),
	_isHillighted(false),
	_isDeformed(false) { }
