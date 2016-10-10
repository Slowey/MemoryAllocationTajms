#version 430
layout (location = 0) in vec3 position;
uniform mat4 MVP;
out vec4 posF;
void main() 
{
	posF = MVP * vec4(position, 1.0);
	gl_Position = posF;
}