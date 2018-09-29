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

	float dy = 1.0f / resolution.y;

	for(int i = 0; i < filter_size; ++i)
	{
		float yOffset = dy * (i - filter_size / 2);
		sum += filter_1d[i] * texture(image, UV + vec2(0.0f, yOffset));
	}

	if(USE_ABS)
	{
		color = abs(sum);
	}
	else
	{
		color = sum;
	}
	

	//color = texture(image, UV + vec2(0.0f, 1.0f / resolution.y));
}