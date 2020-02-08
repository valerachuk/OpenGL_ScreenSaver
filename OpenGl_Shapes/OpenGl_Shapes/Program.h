#pragma once
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <memory>
#include "Shape.h"
#include "ShapeUnion.h"
#include "Buffer.h"
#include "RenderSystem.h"
#include "Window.h"
#include "ShapeData.h"


class Program {
private:
	Program();
	static void onKeyCallback(KeyCode, Action, Modifier);
	glm::vec2 moveAxis;
	float moveSpeed;

public:
	static Program& getInstance();
	void Start();
};