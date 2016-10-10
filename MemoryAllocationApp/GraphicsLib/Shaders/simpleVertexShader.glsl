#version 430
in vec3 pos;
out vec4 posF;
void main() 
{
	posF = vec4(pos.xyz,1.0);
	gl_Position = posF;
}