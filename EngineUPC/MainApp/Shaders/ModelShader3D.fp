#version 130

in vec3 fragmentNormal;
in vec2 fragmentUV;

out vec4 color;

uniform sampler2D sampler;
uniform vec4 ambientColor;

void main()
{
	color = (texture(sampler, fragmentUV))* ambientColor;
}