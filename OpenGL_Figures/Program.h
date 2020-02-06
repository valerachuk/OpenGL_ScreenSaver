#pragma once
#include "RenderSystem.h"
#include "Window.h"
#include <memory>

class Program {
private:
	Program();
	~Program();

public:
	static Program& getInstance();
	void Start();
};