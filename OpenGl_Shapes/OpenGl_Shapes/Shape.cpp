#include "Shape.h"

void Shape::clampCanvasFit()
{
	std::function<float(float, float)> cutOver = [](float value, float max) {return value > max ? max - value : 0; };
	std::function<float(float, float)> cutUnder = [](float value, float min) {return value < min ? min - value : 0; };
	
	glm::vec2 clampVector = glm::vec2(0.0f);
	
	const BoundingBox& boundingBox = calcBoundingBox();

	clampVector.x = cutOver(boundingBox._right, 1.0f);
	clampVector.x = clampVector.x == 0 ? cutUnder(boundingBox._left, -1.0f) : clampVector.x;

	clampVector.y = cutOver(boundingBox._top, 1.0f);
	clampVector.y = clampVector.y == 0 ? cutUnder(boundingBox._bottom, -1.0f) : clampVector.y;

	translate(clampVector);
}

BoundingBox Shape::calcBoundingBox() const
{
	return BoundingBox(_position.y + _scale.y / 2, _position.y - _scale.y / 2, _position.x - _scale.x / 2, _position.x + _scale.x / 2);
}

glm::mat4 Shape::calcShapeMatrix(const glm::vec2& pos)
{
	glm::mat4 matrix(1.0f);
	matrix = glm::translate(matrix, glm::vec3(pos, 0.0f));
	matrix = glm::scale(matrix, glm::vec3(_scale, 1.0f));
	return matrix;
}

glm::mat4 Shape::calcShapeMatrix()
{
	glm::mat4 matrix(1.0f);
	matrix = glm::translate(matrix, glm::vec3(_position, 0.0f));
	matrix = glm::scale(matrix, glm::vec3(_scale, 1.0f));
	return matrix;
}

void Shape::fillTrail()
{
	if (_trail.size() > 0 && _trail.front() == _position || !_hasTrail)
		return;

	_trail.push_front(_position);
	while (_trail.size() > START_OPACITY/K_OPACITY)
	{
		_trail.pop_back();
	}
}

void Shape::drawTrail()
{
	float opacity = START_OPACITY;
	for (std::deque<glm::vec2>::iterator iter = _trail.begin(); iter != _trail.end() && opacity > 0; iter++, opacity -= K_OPACITY) {
		RenderSystem::getInstance().setShapeTransform(calcShapeMatrix(*iter));
		glm::vec4 newColor = _color;
		newColor.a *= opacity;
		RenderSystem::getInstance().setColor(newColor);
		RenderSystem::getInstance().render(_buffer->getVAO(), _buffer->getVertexCount());
	}
}

void Shape::setScale(const glm::vec2& scale)
{
	_scale = scale;
}

void Shape::setColor(const glm::vec4& color)
{
	_color = color;
}

void Shape::setTrail(bool state)
{
	_hasTrail = state;

	if (!_hasTrail)
	{
		_trail.clear();
	}
}

void Shape::setHilighed(bool state)
{
	_isHillighted = state;
}

void Shape::setDeformed(bool state)
{
	if (state && !_isDeformed)
		_scale /= DEFORM_FACTOR;
	else if (!state && _isDeformed)
		_scale *= DEFORM_FACTOR;

	_isDeformed = state;
}

void Shape::setHidden(bool state)
{
	_isHidden = state;
}


void Shape::translate(const glm::vec2& offset)
{
	_position += offset;
	fillTrail();
}

bool Shape::isOtherCollision(const Shape& other)
{
	return (_position.x + _scale.x / 2 >= other._position.x - other._scale.x / 2 ||
			_position.x - _scale.x / 2 <= other._position.x + other._scale.x / 2) &&
			(_position.y + _scale.y / 2 >= other._position.y - other._scale.y / 2 ||
			_position.y - _scale.y / 2 <= other._position.y + other._scale.y / 2);
}

void Shape::draw()
{
	if (_isHidden)
		return;

	drawTrail();

	RenderSystem::getInstance().setShapeTransform(calcShapeMatrix());
	RenderSystem::getInstance().setColor(_color);
	RenderSystem::getInstance().render(_buffer->getVAO(), _buffer->getVertexCount());
}

void Shape::print(std::ostream& stream, std::string indent) const
{
	stream << indent << _id << ") Type:Shape, Color: (" << _color.r << ", " << _color.g << ", " << _color.b
		<< ") Scale: (" << _scale.x << ", " << _scale.y
		<< ") Position: (" << _position.x << ", " << _position.y
		<< "), Deformed: " << _isDeformed
		<< ", Hilighted: " << _isHillighted 
		<< ", Hidden: " << _isHidden
		<< std::endl;

}

Shape::Shape(std::shared_ptr<Buffer> buffer) :
	_scale(glm::vec2(1.0f)),
	_position(glm::vec2(0.0f)),
	_color(glm::vec4(0.0f)),
	_isHillighted(false),
	_isDeformed(false),
	_trail(std::deque<glm::vec2>()),
	_hasTrail(false),
	_isHidden(false),
	_buffer(buffer) { }
