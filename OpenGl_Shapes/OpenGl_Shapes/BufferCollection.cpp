#include "BufferCollection.h"

const std::shared_ptr<Buffer>& BufferCollection::getBuffer(std::string key)
{
	static BufferCollection inst;
	return inst._buffers[key];
}

BufferCollection::BufferCollection() : _buffers(std::map<std::string, std::shared_ptr<Buffer>>())
{
	_buffers["triangle"] = std::make_shared<Buffer>(
		std::vector<glm::vec2>{
		glm::vec2(-0.5f, -0.5f),
			glm::vec2(0.5f, -0.5f),
			glm::vec2(0.0f, 0.5f),
	});

	_buffers["square"] = std::make_shared<Buffer>(
		std::vector<glm::vec2>{
		glm::vec2(0.5f, 0.5f),
			glm::vec2(-0.5f, 0.5f),
			glm::vec2(-0.5f, -0.5f),
			glm::vec2(0.5f, -0.5f),
	});
}