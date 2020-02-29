#pragma once
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <memory>
#include <functional>
#include <iostream>
#include <string>
#include "Shape.h"
#include "ShapeUnion.h"
#include "Buffer.h"
#include "RenderSystem.h"
#include "Window.h"
#include "ShapeFactory.h"
#include "Interfaces.h"
#include "Memento.h"

class Program {
private:
	Program();
	static void onKeyCallback(KeyCode, Action, Modifier);
	void menu();

	Program& operator=(const Program&) = delete;
	Program(const Program&) = delete;

	glm::vec2 _moveAxis;
	float _moveSpeed;
	ICanvasComponent* _currentSelection;
	ShapeUnion _anchor;

public:
	static Program& getInstance();
	void Start();
};