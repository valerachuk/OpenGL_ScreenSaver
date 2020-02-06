#include "Program.h"

Program::Program()
{
	RenderSystem::getInstance().setShader(std::unique_ptr<Shader>(new Shader("ssd", "sdsd")));
}

Program& Program::getInstance()
{
	static Program inst;
	return inst;
}
