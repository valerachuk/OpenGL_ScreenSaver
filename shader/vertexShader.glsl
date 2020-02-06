#version 330 core

layout (location = 0) in vec2 position;

uniform mat4 _modelMatrix;

void main()
{
    gl_Position = vec4(position, 1.0f, 1.0f);
    
}