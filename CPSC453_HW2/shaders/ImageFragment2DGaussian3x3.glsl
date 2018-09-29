#version 330 core

in vec2 UV;
out vec4 color;

uniform sampler2D image;
uniform ivec2	  resolution;

#define FILTER_SIZE 3
#define USE_ABS false

float filter[FILTER_SIZE * FILTER_SIZE];

void main() {

	vec4 sum = vec4(0.0f);

	filter[0] = 0.04f;  filter[3] = 0.12f; filter[6] = 0.04f;
	filter[1] = 0.12f;  filter[4] = 0.36f; filter[7] = 0.12f;
	filter[2] = 0.04f;  filter[5] = 0.12f; filter[8] = 0.04;

	float dx = 1.0f / resolution.x;
	float dy = 1.0f / resolution.y;

	for(int i = 0; i < FILTER_SIZE; ++i)
	{
		for(int j = 0; j < FILTER_SIZE; ++j)
		{
		float xOffset = dx * (i - FILTER_SIZE / 2);
		float yOffset = dy * (j - FILTER_SIZE / 2);
		sum += filter[i * FILTER_SIZE + j] * texture(image, UV + vec2(xOffset, yOffset));
		}
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