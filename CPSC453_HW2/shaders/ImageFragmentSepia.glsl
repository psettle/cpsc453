#version 330 core

in vec2 UV;
out vec4 color;

uniform sampler2D image;

void main() {
	color = texture(image, UV);

	//values from: https://alastaira.wordpress.com/2013/12/02/sepia-shader/
	float R = 0.393 * color.x + 0.769 * color.y + 0.189 * color.z;
	float G = 0.349 * color.x + 0.686 * color.y + 0.168 * color.z;
	float B = 0.272 * color.x + 0.534 * color.y + 0.131 * color.z;

	color = vec4(R,G,B,color.w);
}