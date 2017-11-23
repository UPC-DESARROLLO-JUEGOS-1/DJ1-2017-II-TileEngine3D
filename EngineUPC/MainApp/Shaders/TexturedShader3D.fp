#version 150

in vec3 fragmentVertex;
in vec3 fragmentNormal;
in vec2 fragmentUV;

out vec4 finalColor;
// ambient
uniform vec4 ambientColor;
uniform sampler2D sampler;

void main() {
	finalColor = texture(sampler, fragmentUV) * ambientColor;
}



