#version 330 core

in vec2 UV;
out vec4 color;

uniform sampler2D image;
uniform ivec2	  resolution;

void main() {
	color = texture( image, UV );
}