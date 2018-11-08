#version 330 core

in vec3 colorOut;
out vec4 color;

void main() {
	color = vec4(colorOut, 1.0f);
}