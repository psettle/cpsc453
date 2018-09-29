#version 330 core

in vec2 UV;
out vec4 color;

uniform sampler2D image;
uniform ivec2	  resolution;

#define FILTER_SIZE 7
#define USE_ABS false

float filter[FILTER_SIZE * FILTER_SIZE];

void main() {

	vec4 sum = vec4(0.0f);

	float filter1D[FILTER_SIZE];
	filter1D[0] = 0.03;
	filter1D[1] = 0.11;
	filter1D[2] = 0.22;
	filter1D[3] = 0.28;
	filter1D[4] = 0.22;
	filter1D[5] = 0.11;
	filter1D[6] = 0.03;

	for(int i = 0; i < FILTER_SIZE; ++i)
	{
		for(int j = 0; j < FILTER_SIZE; ++j)
		{
		filter[i * FILTER_SIZE + j] = filter1D[i] * filter1D[j];
		}
	}

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