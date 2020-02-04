#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

class Buffer {
public:
	Buffer(const std::vector<glm::vec2>& vertices);
	~Buffer();

	const GLuint& getVAO() const;
	const GLuint& getVertexCount() const;

private:
	GLuint VAO, VBO;
	size_t vertexCount;

};