#include "Buffer.h"

Buffer::Buffer(const std::vector<glm::vec2>& vertices)
{
	vertexCount = vertices.size();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * 2 * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

Buffer::~Buffer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

const GLuint& Buffer::getVAO() const
{
	return VAO;
}

const GLuint& Buffer::getVertexCount() const
{
	return vertexCount;
}
