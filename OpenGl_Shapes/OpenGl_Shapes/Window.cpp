#include "Window.h"

Window::Window() : 
	_keyCallback(nullptr)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	_handle = glfwCreateWindow(650, 650, "Shapes", nullptr, nullptr);

	if (_handle == nullptr)
	{
		throw std::runtime_error("Failed to create window");
	}
	glfwMakeContextCurrent(_handle);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Failed to initialize GLEW");
	}

	glfwSetWindowUserPointer(_handle, this);
	glfwSetKeyCallback(_handle, internalKeyCallback);

}

Window::~Window()
{
	glfwDestroyWindow(_handle);
}

void Window::internalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto handle = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (handle->_keyCallback != nullptr)
	{
		handle->_keyCallback(static_cast<KeyCode>(key), static_cast<Action>(action), static_cast<Modifier>(mods));
	}
}

Window& Window::getInstance()
{
	static Window inst;
	return inst;
}

uint32_t Window::getWidth() const
{
	int width, height;
	glfwGetFramebufferSize(_handle, &width, &height);
	return width;
}

uint32_t Window::getHeight() const
{
	int width, height;
	glfwGetFramebufferSize(_handle, &width, &height);
	return height;
}

void Window::setKeyCallback(const KeyCallback& keyCallback)
{
	_keyCallback = keyCallback;
}

GLFWwindow* Window::getGLFWHandle()
{
	return _handle;
}

void Window::hideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void Window::showConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

void Window::showWindow()
{
	glfwShowWindow(_handle);
}

void Window::hideWindow()
{
	glfwHideWindow(_handle);
}