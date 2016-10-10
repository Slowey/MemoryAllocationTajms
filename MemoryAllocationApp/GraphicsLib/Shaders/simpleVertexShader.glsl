#version 430
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 MVP;

out vec4 posF;
out vec2 texCoordF;

void main() 
{
	posF = MVP * vec4(position, 1.0);
	texCoordF = texCoord;
	gl_Position = posF;
}