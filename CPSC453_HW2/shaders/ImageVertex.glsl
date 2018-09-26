#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 dataUV;

out vec2 UV;
out vec3 fragPos;

uniform mat4 model_matrix;

void main() {
	gl_Position = model_matrix * vec4(position, 1.0f);

	UV = dataUV;
	fragPos = vec3(gl_Position);
}