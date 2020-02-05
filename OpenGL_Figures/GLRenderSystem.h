#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Shader.h"

class GLRenderSystem
{
private:
	glm::vec4 _color;
	glm::mat4 _figureTransform;

	Shader _shader;

	void sendUniformsToShader();

public:
	GLRenderSystem(const Shader& shader);

	static void clearDisplay(float red, float green, float blue);

	void render(GLuint VAO, GLuint verticesCount);
	
	void setColor(const glm::vec4& color);
	void setFigureTransform(const glm::mat4&);
};