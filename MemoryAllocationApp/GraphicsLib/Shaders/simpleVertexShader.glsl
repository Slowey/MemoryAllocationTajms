#version 430
in vec3 pos;
void main() 
{
	gl_Position = vec4(pos.xyz, 1.0);
}