#version 330 core

in vec2 UV;
out vec4 color;

uniform sampler2D image;

void main() {
	color = texture(image, UV);

	float G_temp = color.y;

	color.y = color.x;
	color.x = G_temp;
}