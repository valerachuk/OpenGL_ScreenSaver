#include "Program.h"

Program::Program()
{
	glfwInit();
	glewInit();

	Window::getInstance().setKeyCallback(onKeyCallback); //first
	RenderSystem::getInstance().setShader(std::unique_ptr<Shader>(new Shader("../shader/vertexShader.glsl", "../shader/fragmentShader.glsl")));
}

void Program::onKeyCallback(KeyCode code, Action action, Modifier modif)
{
}

Program& Program::getInstance()
{
	static Program inst;
	return inst;
}

void Program::Start()
{
	Shape shape = Shape(std::shared_ptr<Buffer>(new Buffer(ShapePoints::getSQUARE())));
	//shape.setColor(glm::vec4(1.0f));

	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(Window::getInstance().getGLFWHandle()))
	{
		glfwWaitEvents();

		RenderSystem::clearDisplay(1, 1, 1);
		shape.draw();

		glfwSwapBuffers(Window::getInstance().getGLFWHandle());
	}
}
