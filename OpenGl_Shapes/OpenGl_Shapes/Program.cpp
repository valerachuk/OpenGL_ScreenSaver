#include "Program.h"

Program::Program() : 
	_moveAxis(glm::vec2(0.0f)),
	_moveSpeed(0.02f),
	_currentSelection(nullptr),
	_anchor(ShapeUnion())
{
	glewInit();
	glfwInit();

	Window::getInstance().setKeyCallback(onKeyCallback); //first
	RenderSystem::getInstance().setShader(
		std::make_unique<Shader>("../../shader/vertexShader.glsl", "../../shader/fragmentShader.glsl"));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_anchor.setId(0);
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
	Memento memento( "savings.txt" );

	const std::function<void(ICanvasComponent*)> changeProps = [](ICanvasComponent* shape) {
		std::cout << "Enter color <R, G, B, A> (0.0f - 1.0f), or type -1 to skip: ";
		glm::vec4 newColor(1.0f);
		std::cin >> newColor.r;
		if (newColor.r != -1)
		{
			std::cin >> newColor.g;
			std::cin >> newColor.b;
			std::cin >> newColor.a;
			shape->setColor(newColor);
		}

		std::cout << "Enter scale <X, Y> (0.0f - 1.0f), or type -1 to skip: ";
		glm::vec2 newScale(1.0f);
		std::cin >> newScale.x;
		if (newScale.x != -1)
		{
			std::cin >> newScale.y;
			glm::clamp(newScale, glm::vec2(0.0f), glm::vec2(1.0f));
			shape->setScale(newScale);
		}

		std::cout << "Enter position <X, Y>, or type -1 to skip: ";
		glm::vec2 newPos(1.0f);
		std::cin >> newPos.x;
		if (newPos.x != -1)
		{
			std::cin >> newPos.y;
			shape->setPos(newPos);
		}

		std::cout << "Enter hidden state (0, 1), or -1 to skip: ";
		int state;
		std::cin >> state;
		if (state == 1 || state == 0)
		{
			shape->setHidden(state);
		}

		std::cout << "Enter deformed state (0, 1), or -1 to skip: ";
		std::cin >> state;
		if (state == 1 || state == 0)
		{
			shape->setDeformed(state);
		}

		std::cout << "Enter trail state (0, 1), or -1 to skip: ";
		std::cin >> state;
		if (state == 1 || state == 0)
		{
			shape->setTrail(state);
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
			std::cout << "commands:\n\thelp\n\tprint\n\tselect\n\tadd\n\tedit\n\tload\n\tsave\n\tclone\n\trecord\n\tplay\n\tquit" << std::endl;
		}
		else if (command == "print") {
			_anchor.print(std::cout);
		}
		else if (command == "record")
		{
			std::cout << "Enter id: ";
			int id;
			std::cin >> id;
			Shape* selection = dynamic_cast<Shape*>(_anchor.getById(id));

			if (!selection)
				std::cout << "ERROR: Invalid selection" << std::endl;
			else
			{
				std::cout << "Start recording" << std::endl;
				PathRecorder::getInstance().startRecording(selection);
			}
		}
		else if (command == "play")
		{
			if (PathRecorder::getInstance().hasItem())
			{
				PathRecorder::getInstance().startPlaying();
				std::cout << "Start playing" << std::endl;
			}
			else
			{
				std::cout << "Cannot start playing, execute record ad first" << std::endl;
			}
		}
		else if (command == "save")
		{
			try
			{
				memento.serialize(static_cast<ShapeUnion*>(&_anchor));
				std::cout << "Done" << std::endl;
			}
			catch (std::exception & e)
			{
				std::cout << "ERROR: " << e.what() << std::endl;
			}
		}
		else if (command == "load")
		{
			try
			{
				_anchor = memento.deserialize();
				_currentSelection = nullptr;
				std::cout << "Done" << std::endl;
			}
			catch (std::exception& e)
			{
				std::cout << "ERROR: " << e.what() << std::endl;
			}
		}
		else if (command == "select") {
			std::cout << "Enter id: ";
			int id;
			std::cin >> id;
			ICanvasComponent* selection = dynamic_cast<ICanvasComponent*>(_anchor.getById(id));

			if (!selection)
				std::cout << "ERROR: Invalid selection" << std::endl;
			else
			{
				_currentSelection = selection;
				std::cout << "Done" << std::endl;
			}
		}
		else if (command == "edit") {
			int id;
			std::cout << "Enter item's id: ";
			std::cin >> id;
			ICanvasComponent* shape;
			if (!(shape = dynamic_cast<ICanvasComponent*>(_anchor.getById(id))))
			{
				std::cout << "ERROR: Invalid id!" << std::endl;
				continue;
			}
			changeProps(shape);
		}
		else if (command == "clone")
		{
			int id;
			std::cout << "Enter id to clone: ";
			std::cin >> id;
			ICanvasComponent* toClone = dynamic_cast<ICanvasComponent*>(_anchor.getById(id));

			if (!toClone)
			{
				std::cout << "Invalid id: " << id << std::endl;
				continue;
			}
			
			int parentId;
			std::cout << "Enter parent id: ";
			std::cin >> parentId;
			ShapeUnion* newParent = dynamic_cast<ShapeUnion*>(_anchor.getById(parentId));

			if (!newParent)
			{
				std::cout << "Invalid id: " << id << std::endl;
				continue;
			}

			std::unique_ptr<ICanvasComponent> clone = std::unique_ptr<ICanvasComponent>(static_cast<ICanvasComponent*>(toClone->deepClone()));
			newParent->add(clone);
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
			std::cout << "Enter type: <union/square/triangle/star/octagon>: ";
			std::cin >> type;

			ICanvasComponent* newElem;

			if (type == "union") {
				newElem = new ShapeUnion();
			}
			else {
				newElem = static_cast<ICanvasComponent*>(ShapeFactory::getShape(type));
				if (newElem == nullptr)
					continue;
			}
				
			newElem->setId(Id);
			
			if (type != "union")
				changeProps(newElem);

			auto toAdd = std::unique_ptr<ICanvasComponent>(newElem);
			parent->add(toAdd);
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

void Program::start()
{
	menu();

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
		PathRecorder::getInstance().execute();
		_anchor.draw();

		glfwSwapBuffers(Window::getInstance().getGLFWHandle());
	}
}
