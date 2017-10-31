#version 130

in vec3 fragmentNormal;

out vec4 color;

uniform vec4 ambientColor;

void main()
{
	color = ambientColor;
}