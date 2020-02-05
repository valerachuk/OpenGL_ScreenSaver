#include "GLRenderSystem.h"

GLRenderSystem::GLRenderSystem(const Shader& shader) :
	_color(glm::vec4(1.0f)),
	_figureTransform(glm::mat4(1.0f)),
	_shader(shader) {}

void GLRenderSystem::clearDisplay(float red, float green, float blue)
{
	glClearColor(red, green, blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void GLRenderSystem::render(GLuint VAO, GLuint verticesCount)
{
	glBindVertexArray(VAO);

	_shader.UseProgram();
	sendUniformsToShader();

	glDrawArrays(GL_TRIANGLES, 0, verticesCount);
	glBindVertexArray(0);
}

void GLRenderSystem::setColor(const glm::vec4& color)
{
	_color = color;
}

void GLRenderSystem::setFigureTransform(const glm::mat4& transform)
{
	_figureTransform = transform;
}

void GLRenderSystem::sendUniformsToShader()
{
	_shader.setMat4Uniform("modelMatrix", _figureTransform);
	_shader.setVec4Uniform("lightPos", _color);
}
