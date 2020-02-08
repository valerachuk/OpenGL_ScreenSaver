#include "Program.h"

Program::Program() : 
	moveAxis(glm::vec2(0.0f)),
	moveSpeed(0.04f)
{
	glfwInit();
	glewInit();

	Window::getInstance().setKeyCallback(onKeyCallback); //first
	RenderSystem::getInstance().setShader(std::unique_ptr<Shader>(new Shader("../../shader/vertexShader.glsl", "../../shader/fragmentShader.glsl")));
}

void Program::onKeyCallback(KeyCode code, Action action, Modifier modif)
{
	glm::vec2& axis = Program::getInstance().moveAxis;
	if (action == Action::Press)
	{
		switch (code)
		{
		case KeyCode::W:
			axis.y = 1.0f;
			break;
		case KeyCode::A:
			axis.x = -1.0f;
			break;
		case KeyCode::S:
			axis.y = -1.0f;
			break;
		case KeyCode::D:
			axis.x = 1.0f;
			break;
		}
	}
	else if (action == Action::Release) {
		switch (code)
		{
		case KeyCode::W:
		case KeyCode::S:
			axis.y = 0.0f;
			break;
		case KeyCode::A:
		case KeyCode::D:
			axis.x = 0.0f;
			break;
		}
	}

	//Program::getInstance().moveAxis = glm::normalize(axis);
}

Program& Program::getInstance()
{
	static Program inst;
	return inst;
}

void Program::Start()
{
	Shape shape = Shape(std::shared_ptr<Buffer>(new Buffer(ShapeData::getTriangle())));
	//shape.setColor(glm::vec4(1.0f));

	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(Window::getInstance().getGLFWHandle()))
	{
		glfwWaitEvents();

		RenderSystem::clearDisplay(1, 1, 1);
		shape.draw();
		shape.translate(moveAxis * moveSpeed);

		glfwSwapBuffers(Window::getInstance().getGLFWHandle());
	}
}
