#pragma once
#include <glm/glm.hpp>
#include <vector>

class ShapeData {
public:
	static std::vector<glm::vec2> getTriangle() {
		return std::vector<glm::vec2>{
			glm::vec2(-0.5f, -0.5f),
			glm::vec2(0.5f, -0.5f),
			glm::vec2(0.0f, 0.5f),
		};
	}

	static std::vector<glm::vec2> getSquare() {
		return std::vector<glm::vec2>{
			glm::vec2(0.5f, 0.5f),
			glm::vec2(-0.5f, 0.5f),
			glm::vec2(-0.5f, -0.5f),
			glm::vec2(0.5f, -0.5f),
		};
	}
};

