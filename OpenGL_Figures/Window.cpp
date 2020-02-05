#include "Window.h"

Window::Window() : 
	keyCallback(nullptr)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	handle = glfwCreateWindow(650, 650, "Shapes", nullptr, nullptr);

	if (handle == nullptr)
	{
		throw new std::runtime_error("Failed to create window");
	}
	glfwMakeContextCurrent(handle);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		throw new std::runtime_error("Failed to initialize GLEW");
	}

	glfwSetWindowUserPointer(handle, this);
	glfwSetKeyCallback(handle, internalKeyCallback);
}

Window::~Window()
{
	glfwDestroyWindow(handle);
}

void Window::internalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto handle = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (handle->keyCallback != nullptr)
	{
		handle->keyCallback((KeyCode)key, (Action)action, (Modifier)mods);
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
	glfwGetFramebufferSize(handle, &width, &height);
	return width;
}

uint32_t Window::getHeigth() const
{
	int width, height;
	glfwGetFramebufferSize(handle, &width, &height);
	return height;
}

void Window::setKeyCallback(const KeyCallback& _keyCallback)
{
	keyCallback = _keyCallback;
}

GLFWwindow* Window::getGLFWHandle()
{
	return handle;
}

void Window::hideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void Window::showConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool Window::requestFilePath(char* path)
{
	OPENFILENAMEA ofn;

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Ascii Stereolithography (.stl)\0*.stl";
	ofn.lpstrFile = path;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrTitle = "Privet, let me open your file...";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

	return GetOpenFileNameA(&ofn);
}
