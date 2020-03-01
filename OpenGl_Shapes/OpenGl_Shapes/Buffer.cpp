#include "Buffer.h"

Buffer::Buffer(const std::vector<glm::vec2>& vertices, const std::string& name) : _shapeName(name)
{
	_vertexCount = vertices.size();

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertexCount * 2 * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), static_cast<GLvoid*>(0));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

Buffer::~Buffer()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
}

const GLuint& Buffer::getVao() const
{
	return _vao;
}

const GLuint& Buffer::getVertexCount() const
{
	return _vertexCount;
}

const std::string& Buffer::getName() const
{
	return _shapeName;
}