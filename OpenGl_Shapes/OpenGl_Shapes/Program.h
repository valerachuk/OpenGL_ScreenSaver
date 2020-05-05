#pragma once
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <memory>
#include <functional>
#include <iostream>
#include <string>
#include "Buffer.h"
#include "Shape.h"
#include "RenderSystem.h"
#include "Window.h"
#include <thread>
#include <mutex>
#include "ScreenSaverShape.h"

class Program {
private:
	Program();

	Program& operator=(const Program&) = delete;
	Program(const Program&) = delete;

	std::vector<std::unique_ptr<ScreenSaverShape>> _shapes;
	std::mutex _mutex;

	void draw();
	void addShapes();
	void processTargets();
	void moveShapes();
	void deleteShapes();

public:
	static Program& getInstance();
	void start();
};