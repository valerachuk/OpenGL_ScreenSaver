#pragma once
#include <glm/glm.hpp>
#include <vector>


class ShapePoints {
	public:
	static std::vector<glm::vec2> getSQUARE() {
		return std::vector<glm::vec2>{
			glm::vec2(0.1f, 0.0f),
				glm::vec2(-0.3f, 0.3f),
				glm::vec2(-0.3f, -0.3f),
				glm::vec2(0.3f, -0.3f),
		};
	}

};