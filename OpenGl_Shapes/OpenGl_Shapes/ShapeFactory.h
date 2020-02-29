#pragma once
#include "Buffer.h"
#include "Shape.h"
#include <string>

class ShapeFactory {
private:
	std::shared_ptr<Buffer> _triangleBuffer = std::make_shared<Buffer>(
		std::vector<glm::vec2>{
			glm::vec2(-0.5f, -0.5f),
			glm::vec2(0.5f, -0.5f),
			glm::vec2(0.0f, 0.5f),
	}, "triangle");

	std::shared_ptr<Buffer> _squareBuffer = std::make_shared<Buffer>(
		std::vector<glm::vec2>{
			glm::vec2(0.5f, 0.5f),
			glm::vec2(-0.5f, 0.5f),
			glm::vec2(-0.5f, -0.5f),
			glm::vec2(0.5f, -0.5f),
	}, "square");

	std::shared_ptr<Buffer> _starBuffer = std::make_shared<Buffer>(
		std::vector<glm::vec2>{
			glm::vec2(0.0f, 0.0f),
			glm::vec2(0.0f, 0.5f),
			glm::vec2(0.1f, 0.1f),
			glm::vec2(0.5f, 0.0f),
			glm::vec2(0.1f, -0.1f),
			glm::vec2(0.0f, -0.5f),
			glm::vec2(-0.1f, -0.1f),
			glm::vec2(-0.5f, 0.0f),
			glm::vec2(-0.1f, 0.1f),
			glm::vec2(0.0f, 0.5f),
	}, "star");

	std::shared_ptr<Buffer> _octagonBuffer = std::make_shared<Buffer>(
		std::vector<glm::vec2>{
			glm::vec2(0.0f, 0.0f),
			glm::vec2(-0.25f, 0.5f),
			glm::vec2(0.25f, 0.5f),
			glm::vec2(0.5f, 0.25f),
			glm::vec2(0.5f, -0.25f),
			glm::vec2(0.25f, -0.5f),
			glm::vec2(-0.25f, -0.5f),
			glm::vec2(-0.5f, -0.25f),
			glm::vec2(-0.5f, 0.25f),
			glm::vec2(-0.25f, 0.5f),
	}, "octagon");

	Shape _triangle = Shape(_triangleBuffer);
	Shape _square = Shape(_squareBuffer);
	Shape _star = Shape(_starBuffer);
	Shape _octagon = Shape(_octagonBuffer);

	ShapeFactory();

public:
	static Shape* getShape(const std::string& type);
};