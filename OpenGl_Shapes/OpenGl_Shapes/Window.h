#pragma once
#include <functional>
#include <string>
#include <iostream>
#include <GL\glew.h>	
#include <glfw\glfw3.h>	
#include <Windows.h>

enum class Modifier {
	NoModifier = 0,
	Shift = 1,
	Control = 2,
	Alt = 4,
	Super = 8,
};

enum class Action {
	Release = 0,
	Press = 1,
	Repeat = 2,
};

enum class KeyCode {
	UNKNOWN = -1,
	Space = 32,
	LeftShift = 340,
	
	W = 87,
	A = 65,
	S = 83,
	D = 68,

	O = 79,
	C = 67,

	Up = 265,
	Down = 264,
	Right = 262,
	Left = 263,

	F1 = 290,
	F2 = 291,
	F3 = 292,
	F4 = 293,
	F5 = 294,
	F6 = 295,
	F7 = 296,
	F8 = 297,
	F9 = 298,
	F10 = 299,
	F11 = 300,
	F12 = 301,
};

class Window {
private:
	using KeyCallback = std::function<void(KeyCode, Action, Modifier)>;
	GLFWwindow* handle;
	KeyCallback keyCallback;
	~Window();
	Window();

	static void internalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

public:
	static Window& getInstance();

	uint32_t getWidth() const;
	uint32_t getHeigth() const;
	void setKeyCallback(const KeyCallback&);

	GLFWwindow* getGLFWHandle();

	static void hideConsole();
	static void showConsole();
	void showWindow();
	void hideWindow();

	static bool requestFilePath(char*);

};