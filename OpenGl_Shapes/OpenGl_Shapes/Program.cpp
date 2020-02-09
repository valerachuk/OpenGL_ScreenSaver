#include "Program.h"

Program::Program() : 
	_moveAxis(glm::vec2(0.0f)),
	_moveSpeed(0.02f),
	_currentSelection(nullptr)
{
	glfwInit();
	glewInit();
	Window::getInstance().setKeyCallback(onKeyCallback); //first
	RenderSystem::getInstance().setShader(std::unique_ptr<Shader>(new Shader("../../shader/vertexShader.glsl", "../../shader/fragmentShader.glsl")));
}

void Program::onKeyCallback(KeyCode code, Action action, Modifier modif)
{
	if (code == KeyCode::F1 && action == Action::Press)
	{
		Program::getInstance().menu();
		return;
	}

	glm::vec2& axis = Program::getInstance()._moveAxis;
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

	if (glm::length(axis) > 0)
		axis = glm::normalize(axis);

}

void Program::menu()
{
	std::function<void(Shape*)> changeProps = [](Shape* shape) {
		std::cout << "Enter new color <R, G, B> (0.0f - 1.0f), or type -1 to skip: ";
		glm::vec4 newColor(1.0f);
		std::cin >> newColor.r;
		if (newColor.r != -1)
		{
			std::cin >> newColor.g;
			std::cin >> newColor.b;
			shape->setColor(newColor);
		}

		std::cout << "Enter new scale <X, Y> (0.0f - 1.0f), or type -1 to skip: ";
		glm::vec2 newScale(1.0f);
		std::cin >> newScale.x;
		if (newScale.r != -1)
		{
			std::cin >> newScale.y;
			glm::clamp(newScale, glm::vec2(0.0f), glm::vec2(1.0f));
			shape->setScale(newScale);
		}

	};

	Window::getInstance().hideWindow();
	Window::showConsole();
	std::string command;
	do
	{
		std::cout << "-----------------------------" << std::endl;
		std::cin >> command;

		if (command == "?" || command == "help") {
			std::cout << "commands:\n\thelp\n\tprint\n\tselect\n\tadd\n\tedit\n\tquit" << std::endl;
		}
		else if (command == "print") {
			_anchor.print(std::cout);
		}
		else if (command == "select") {
			std::cout << "Enter id: ";
			int id;
			std::cin >> id;
			ICanvasComponent* selection = dynamic_cast<ICanvasComponent*>(_anchor.getById(id));

			if (!selection)
				std::cout << "ERROR: Invalid selection" << std::endl;
			else
				_currentSelection = selection;
		}
		else if (command == "edit") {
			int Id;
			std::cout << "Enter item's id: ";
			std::cin >> Id;
			Shape* shape;
			if (!(shape = dynamic_cast<Shape*>(_anchor.getById(Id))))
			{
				std::cout << "ERROR: Invalid id!" << std::endl;
				continue;
			}
			changeProps(shape);
		}
		else if (command == "add") {
			int parentId;
			std::cout << "Enter parent id: ";
			std::cin >> parentId;
			ShapeUnion* parent;

			if (!(parent = dynamic_cast<ShapeUnion*>(_anchor.getById(parentId)))) {
				std::cout << "ERROR: Invalid parent" << std::endl;
				continue;
			}

			int Id;
			std::cout << "Enter new item's id: ";
			std::cin >> Id;

			if (_anchor.getById(Id))
			{
				std::cout << "ERROR: Id already exist!" << std::endl;
				continue;
			}

			std::string type;
			std::cout << "Enter type: <union/square/triangle>: ";
			std::cin >> type;

			if (type == "union") {
				std::unique_ptr<ICanvasComponent> newUnion = std::make_unique<ShapeUnion>();
				newUnion->setId(Id);
				parent->Add(newUnion);
				std::cout << "new Union added!" << std::endl;
				continue;
			}

			std::shared_ptr<Buffer> buffer = BufferCollection::getBuffer(type);

			if (!buffer)
			{
				std::cout << "ERROR: Invalid type!" << std::endl;
				continue;
			}

			Shape* newShape = new Shape(buffer);
			newShape->setId(Id);
			changeProps(newShape);
			auto toAdd = std::unique_ptr<ICanvasComponent>((ICanvasComponent*)newShape);
			parent->Add(toAdd);
		}

	} while (command != "quit");

	Window::hideConsole();
	Window::getInstance().showWindow();

}

Program& Program::getInstance()
{
	static Program inst;
	return inst;
}

void Program::Start()
{
	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(Window::getInstance().getGLFWHandle()))
	{
		glfwPollEvents();

		RenderSystem::clearDisplay(1, 1, 1);
		if (_currentSelection)
		{
			_currentSelection->translate(_moveAxis * _moveSpeed);
			_currentSelection->clampCanvasFit();
		}
		_anchor.draw();

		glfwSwapBuffers(Window::getInstance().getGLFWHandle());
	}
}
