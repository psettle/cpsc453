#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 dataUV;

out vec2 UV;
out vec3 fragPos;
out vec3 origin;

uniform mat4 MVP;
uniform mat4 model;

void main() {
	gl_Position = MVP * vec4(position, 1.0f);
	UV = dataUV;
	fragPos = vec3(model * vec4(position, 1.0f));
	origin = vec3(model * vec4(vec3(0.0f), 1.0f));
}