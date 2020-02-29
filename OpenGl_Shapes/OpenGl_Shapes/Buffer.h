#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <string>

class Buffer {
public:
	Buffer(const std::vector<glm::vec2>& vertices, const std::string& name);
	~Buffer();

	const GLuint& getVAO() const;
	const GLuint& getVertexCount() const;

	const std::string& getName() const;

private:
	GLuint VAO, VBO;
	size_t vertexCount;
	std::string _shapeName;

};