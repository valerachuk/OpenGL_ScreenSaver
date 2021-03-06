#include "Shader.h"

std::string Shader::readFile(const char* path)
{
    std::ifstream file(path);
    std::stringstream sstream;

    if (!file.is_open()) {
        throw std::runtime_error("Can't open the file!");
    }

    sstream << file.rdbuf();
    std::string shaderString = sstream.str();
    shaderString.push_back(0);
    file.close();

    return shaderString;
}

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) : _shader(0)
{
	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    std::string stupudString = readFile(vertexPath);
    const GLchar* vertexShaderFile = stupudString.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderFile, NULL);
    glCompileShader(vertexShader);

    stupudString = readFile(fragmentPath);
    const GLchar* fragmentShaderFile = stupudString.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderFile, NULL);
    glCompileShader(fragmentShader);

    GLint successVertex;
    GLchar infoLogVertex[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);
    if (!successVertex) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLogVertex);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogVertex << std::endl;
        exit(-1);
    }

    GLint successFragment;
    GLchar infoLogFragment[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragment);
    if (!successFragment) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFragment);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogFragment << std::endl;
        exit(-1);
    }

    _shader = glCreateProgram();
    glAttachShader(_shader, vertexShader);
    glAttachShader(_shader, fragmentShader);
    glLinkProgram(_shader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::useProgram() const{
	glUseProgram(_shader);
}

void Shader::setMat4Uniform(const char* name, const glm::mat4& matrix4)
{
    glUniformMatrix4fv(glGetUniformLocation(_shader, name), 1, GL_FALSE, glm::value_ptr(matrix4));
}

void Shader::setVec4Uniform(const char* name, const glm::vec4& vector4)
{
    glUniform4fv(glGetUniformLocation(_shader, name), 1, glm::value_ptr(vector4));
}

void Shader::setFloatUniform(const char* name, const float& value)
{
    glUniform1f(glGetUniformLocation(_shader, name), value);
}

void Shader::setBoolUniform(const char* name, const bool& value)
{
    glUniform1i(glGetUniformLocation(_shader, name), value);
}
