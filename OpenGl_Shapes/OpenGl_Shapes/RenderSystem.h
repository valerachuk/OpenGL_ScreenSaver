#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Shader.h"

class RenderSystem
{
private:
	glm::vec4 _color;
	glm::mat4 _ShapeTransform;

	std::unique_ptr<Shader> _shader;

	void sendUniformsToShader();
	RenderSystem();
	void checkSahder() const;

public:
	static RenderSystem& getInstance();

	void setShader(std::unique_ptr<Shader>);

	static void clearDisplay(float red, float green, float blue);

	void render(GLuint VAO, size_t verticesCount);
	
	void setColor(const glm::vec4& color);
	void setShapeTransform(const glm::mat4&);
};