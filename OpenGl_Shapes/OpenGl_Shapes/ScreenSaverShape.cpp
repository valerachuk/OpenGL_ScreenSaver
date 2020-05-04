#include "ScreenSaverShape.h"

ScreenSaverShape::ScreenSaverShape(std::shared_ptr<Buffer> buffer) :
	Shape(buffer),
	_target(nullptr),
	_toDelete(false)
{ }

ScreenSaverShape::ScreenSaverShape() : Shape()
{
	static std::shared_ptr<Buffer> _triangleBuffer = std::make_shared<Buffer>(
		std::vector<glm::vec2>{
		glm::vec2(-0.5f, -0.5f),
			glm::vec2(0.5f, -0.5f),
			glm::vec2(0.0f, 0.5f),
	}, "triangle");

	static std::shared_ptr<Buffer> _squareBuffer = std::make_shared<Buffer>(
		std::vector<glm::vec2>{
		glm::vec2(0.5f, 0.5f),
			glm::vec2(-0.5f, 0.5f),
			glm::vec2(-0.5f, -0.5f),
			glm::vec2(0.5f, -0.5f),
	}, "square");

	static std::shared_ptr<Buffer> _starBuffer = std::make_shared<Buffer>(
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

	static std::shared_ptr<Buffer> _octagonBuffer = std::make_shared<Buffer>(
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

	static std::vector<std::shared_ptr<Buffer>> _buffers = { _squareBuffer, _triangleBuffer, _starBuffer, _octagonBuffer };

	static glm::vec3 colors[] = {
	glm::vec3(0.96f, 0.82f, 0.35f),
	glm::vec3(0.94f, 0.81f, 0.77f),
	glm::vec3(0.82f, 0.69f, 0.58f),
	glm::vec3(0.59f, 0.84f, 0.88f),
	glm::vec3(0.53f, 0.69f, 0.29f),
	glm::vec3(0.94f, 0.34f, 0.18f),
	glm::vec3(0.82f, 0.19f, 0.46f),
	glm::vec3(0.32f, 0.52f, 0.63f),
	glm::vec3(0.36f, 0.44f, 0.28f),
	glm::vec3(0.05f, 0.3f, 0.54f)
	};

	_buffer = _buffers[Utils::getInstance().getRandomInt(0, 4)];

	setTrail(true);
	setPos(glm::vec2(Utils::getInstance().getRandomFloat(-1, 1), Utils::getInstance().getRandomFloat(-1, 1)));
	setScale(glm::vec2(Utils::getInstance().getRandomFloat(0.1f, 0.2f), Utils::getInstance().getRandomFloat(0.1f, 0.2f)));
	setColor(glm::vec4(colors[Utils::getInstance().getRandomInt(0, 10)], 1.0f));
}

bool ScreenSaverShape::getDeleteState()
{
	return _toDelete;
}

void ScreenSaverShape::setDeleteState(bool state)
{
	_toDelete = state;
}

ScreenSaverShape* ScreenSaverShape::getTarget()
{
	return _target;
}

void ScreenSaverShape::setTarget(ScreenSaverShape* target)
{
	_target = target;
}