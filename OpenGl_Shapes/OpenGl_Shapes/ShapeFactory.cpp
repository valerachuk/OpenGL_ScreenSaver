#include "ShapeFactory.h"

ShapeFactory::ShapeFactory() {

	_triangle.setColor(glm::vec4(1, 0, 0, 1));
	_triangle.setScale(glm::vec2(0.7f));
	_triangle.setTrail(true);

	_square.setColor(glm::vec4(0, 1, 0, 1));
	_square.setScale(glm::vec2(0.4f, 0.8f));

	_octagon.setColor(glm::vec4(0, 0, 1, 1));
	_octagon.setScale(glm::vec2(0.5f));

	_star.setColor(glm::vec4(0, 1, 1, 1));
	_star.setScale(glm::vec2(0.3f));
	_star.setTrail(true);
}

Shape ShapeFactory::getShape(ShapeType type)
{
	static ShapeFactory factory;
	if (type == ShapeType::Octagon) {
		return factory._octagon;
	}
	else if (type == ShapeType::Square) {
		return factory._square;
	}
	else if (type == ShapeType::Star) {
		return factory._star;
	}
	else if (type == ShapeType::Triangle) {
		return factory._triangle;
	}
}
