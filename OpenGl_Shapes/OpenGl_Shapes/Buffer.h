#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Buffer {
private:
	GLuint _vao, _vbo;
	size_t _vertexCount;
	std::string _shapeName;
	
public:
	Buffer(const std::vector<glm::vec2>& vertices, const std::string& name);
	~Buffer();

	const GLuint& getVao() const;
	const GLuint& getVertexCount() const;

	const std::string& getName() const;

};