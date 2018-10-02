#version 330 core

in vec2 UV;
out vec4 color;

uniform sampler2D image;

void main() {
	color = texture(image, UV);

	float L = 0.333 * color.x + 0.333 * color.y + 0.333 * color.z;

	color = vec4(L,L,L,color.w);

}