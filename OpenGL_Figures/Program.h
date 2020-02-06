#pragma once
#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <memory>
#include "Shape.h"
#include "Buffer.h"
#include "RenderSystem.h"
#include "Window.h"
#include "Figures_data.h"


class Program {
private:
	Program();
	static void onKeyCallback(KeyCode, Action, Modifier);

public:
	static Program& getInstance();
	void Start();
};