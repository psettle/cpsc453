#version 330 core

in vec2 UV;
out vec4 color;

uniform sampler2D image;
uniform ivec2	  resolution;

#define FILTER_SIZE 3
#define USE_ABS true

float filter[FILTER_SIZE * FILTER_SIZE];

void main() {

	vec4 sum = vec4(0.0f);

	filter[0] = -1.0f; filter[3] = -2.0f; filter[6] = -1.0f;
	filter[1] = 0.0f;  filter[4] = 0.0f;  filter[7] = 0.0f;
	filter[2] = 1.0f;  filter[5] = 2.0f;  filter[8] = 1.0f;

	float dx = 1.0f / resolution.x;
	float dy = 1.0f / resolution.y;

	for(int i = 0; i < FILTER_SIZE; ++i)
	{
		for(int j = 0; j < FILTER_SIZE; ++j)
		{
		float xOffset = dx * (i - FILTER_SIZE / 2);
		float yOffset = dx * (j - FILTER_SIZE / 2);
		sum += filter[i * FILTER_SIZE + j] * texture(image, UV - vec2(xOffset, yOffset));
		}
	}

	sum.w = 1.0f; /* Reset alpha so the results actually show up */

	if(USE_ABS)
	{
		color = abs(sum);
	}
	else
	{
		color = sum;
	}
	
}