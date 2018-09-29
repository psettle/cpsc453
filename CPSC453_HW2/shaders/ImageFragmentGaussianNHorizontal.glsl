#version 330 core

in vec2 UV;
out vec4 color;

#define MAX_FILTER_SIZE 200 * 2 + 1
#define USE_ABS false

uniform sampler2D image;
uniform ivec2	  resolution;

uniform int filter_size;
uniform float filter_1d[MAX_FILTER_SIZE];

void main() {
	vec4 sum = vec4(0.0f);

	float dx = 1.0f / resolution.x;

	for(int i = 0; i < filter_size; ++i)
	{
		float xOffset = dx * (i - filter_size / 2);
		sum += filter_1d[i] * texture(image, UV + vec2(xOffset, 0.0f));
	}

	if(USE_ABS)
	{
		color = abs(sum);
	}
	else
	{
		color = sum;
	}
	
}