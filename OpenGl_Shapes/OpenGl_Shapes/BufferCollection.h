#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include "Buffer.h"

class BufferCollection {
private:
	std::map<std::string, std::shared_ptr<Buffer>> _buffers;
	BufferCollection();

	BufferCollection& operator=(const BufferCollection&) = delete;
	BufferCollection(const BufferCollection&) = delete;

public:
	static const std::shared_ptr<Buffer>& getBuffer(std::string key);
};

