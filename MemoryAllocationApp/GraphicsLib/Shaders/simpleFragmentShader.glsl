#version 430
in vec4 posF;
in vec2 texCoordF;

out vec4 color;

uniform sampler2D sampler;

void main() 
{
	// Debug red color
	//color = vec4(1,0,0,0);
	// Texture color
	color = texture2D(sampler, texCoordF);
}