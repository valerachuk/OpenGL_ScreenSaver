#include "Program.h"

Program::Program()
{
	glewInit();
	glfwInit();

	Window::getInstance();
	RenderSystem::getInstance().setShader(
		std::make_unique<Shader>("../../shader/vertexShader.glsl", "../../shader/fragmentShader.glsl"));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Program::draw()
{
	auto shape = new ScreenSaverShape();
	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(Window::getInstance().getGLFWHandle()))
	{
		glfwPollEvents();
		RenderSystem::clearDisplay(1, 1, 1);

		_mutex.lock();
		//std::cout << "Drawing!!" << std::endl;
		for (auto it = _shapes.begin(); it != _shapes.end(); ++it)
		{
			it->get()->draw();
		}
		_mutex.unlock();

		glfwSwapBuffers(Window::getInstance().getGLFWHandle());
	}
}

void Program::addShapes()
{
	while (true)
	{
		_mutex.lock();
		//std::cout << "addShapes" << std::endl;

		while(_shapes.size() < 20)
		{
			_shapes.push_back(std::make_unique<ScreenSaverShape>());
		}
		
		_mutex.unlock();

		std::this_thread::yield();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Program::processTargets()
{
	while (true)
	{
		_mutex.lock();
		//std::cout << "processTargets" << std::endl;

		for (auto it = _shapes.begin(); it != _shapes.end(); ++it)
		{
			if (!it->get()->getTarget())
			{
				int lockCounter = 3;
				ScreenSaverShape* sss;

				do
				{
					sss = _shapes[Utils::getInstance().getRandomInt(0, _shapes.size())].get();
				} while (lockCounter-- && sss == it->get());

				if (lockCounter != -1)
				{
					it->get()->setTarget(sss);
				}
			}
		}

		_mutex.unlock();

		std::this_thread::yield();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Program::moveShapes()
{
	while (true)
	{
		_mutex.lock();
		//std::cout << "moveShapes" << std::endl;

		for (auto it = _shapes.begin(); it != _shapes.end(); ++it)
		{
			if (it->get()->getTarget() && !it->get()->getDeleteState())
			{
				if (it->get()->isIntersects(*it->get()->getTarget()))
				{
					it->get()->getTarget()->setDeleteState(true);
					it->get()->setDeleteState(true);
				}
				
				glm::vec2 direction = it->get()->getTarget()->getPos() - it->get()->getPos();
				direction = glm::normalize(direction);
				direction *= 0.005f;
				//std::cout << "X: " << direction.x << " Y: " << direction.y << std::endl;
				it->get()->translate(direction);
			}
		}

		_mutex.unlock();

		std::this_thread::yield();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

void Program::deleteShapes()
{
	while (true)
	{
		_mutex.lock();
		//std::cout << "deleteShapes" << std::endl;

		
		auto it = _shapes.begin();
		while (it != _shapes.end())
		{
			if (it->get()->getDeleteState())
			{
				for (auto it_ = _shapes.begin(); it_ != _shapes.end(); ++it_)
				{
					if (it_->get()->getTarget() == it->get())
					{
						it_->get()->setTarget(nullptr);
					}
				}
				
				it = _shapes.erase(it);
			}
			else
			{
				++it;
			}
		}

		_mutex.unlock();

		std::this_thread::yield();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}


Program& Program::getInstance()
{
	static Program inst;
	return inst;
}

void Program::start()
{
	std::thread([this] {processTargets(); }).detach();
	std::thread([this] {moveShapes(); }).detach();
	std::thread([this] {deleteShapes(); }).detach();
	std::thread([&] {addShapes(); }).detach();
	draw();
}
