#include "Shape.h"

void Shape::generateTrail()
{
	/*for (float opacity = START_OPACITY, int zIndex = -1; opacity > 0; opacity -= K_OPACITY, zIndex--)
	{
		Shape shape = Shape(_buffer);
		glm::vec4 newColor = _color;
		newColor *= opacity;
		shape.setColor(newColor);
		shape.setPos(_position);
		shape.setZIndex(zIndex);
		_trail.push_back(shape);
	}*/
}

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

glm::mat4 Shape::calcShapeMatrix()
{
	glm::mat4 matrix(1.0f);
	matrix = glm::translate(matrix, glm::vec3(_position, 0.0f));
	matrix = glm::scale(matrix, glm::vec3(_scale, 1.0f));
	return matrix;
}

void Shape::setScale(const glm::vec2& scale)
{
	_scale = scale;
}

void Shape::setPos(const glm::vec2& position)
{
	_position = position;
}

void Shape::setColor(const glm::vec4& color)
{
	_color = color;
}

void Shape::setTrail(bool state)
{
	if (state)
		generateTrail();
	else
		_trail.clear();
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


void Shape::translate(const glm::vec2& offset)
{
	_position += offset;
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
	/*for (auto item = _trail.begin(); item != _trail.end(); item++)
		item->draw();*/

	RenderSystem::getInstance().setShapeTransform(calcShapeMatrix());
	RenderSystem::getInstance().setColor(_color);
	RenderSystem::getInstance().render(_buffer->getVAO(), _buffer->getVertexCount());
}

void Shape::print(std::ostream& stream, std::string indent) const
{
	stream << indent << _id << ") Type:Shape, Color: (" << _color.r << ", "
		<< _color.g << ", " << _color.b << ")" << std::endl;
}

Shape::Shape(std::shared_ptr<Buffer> buffer) :
	_scale(glm::vec2(1.0f)),
	_position(glm::vec2(0.0f)),
	_color(glm::vec4(0.0f)),
	_isHillighted(false),
	_isDeformed(false),
	_trail(std::vector<Shape>()),
	_buffer(buffer) { }
