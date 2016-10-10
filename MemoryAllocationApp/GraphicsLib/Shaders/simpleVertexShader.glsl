#version 430
layout (location = 0) in vec3 position;
uniform mat4 world;
out vec4 posF;
void main() 
{
	posF = world * vec4(position, 1.0);
	gl_Position = posF;
}