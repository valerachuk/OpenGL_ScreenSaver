#include "RenderSystem.h"

RenderSystem::RenderSystem() :
	_color(glm::vec4(1.0f)),
	_ShapeTransform(glm::mat4(1.0f)),
	_shader(nullptr) {}

void RenderSystem::checkSahder() const
{
	if (_shader == nullptr)
		throw std::exception_ptr();
}

RenderSystem& RenderSystem::getInstance()
{
	static RenderSystem inst;
	return inst;
}

void RenderSystem::setShader(std::unique_ptr<Shader> shader)
{
	_shader = std::move(shader);
}

void RenderSystem::clearDisplay(float red, float green, float blue)
{
	glClearColor(red, green, blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSystem::render(GLuint VAO, size_t verticesCount)
{
	checkSahder();

	glBindVertexArray(VAO);

	_shader->UseProgram();
	sendUniformsToShader();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_LINE_LOOP, 0, verticesCount);
	glBindVertexArray(0);
}

void RenderSystem::setColor(const glm::vec4& color)
{
	_color = color;
}

void RenderSystem::setShapeTransform(const glm::mat4& transform)
{
	_ShapeTransform = transform;
}

void RenderSystem::sendUniformsToShader()
{
	checkSahder();

	_shader->setMat4Uniform("_modelMatrix", _ShapeTransform);
	_shader->setVec4Uniform("_color", _color);
}
