#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colorData;

out vec3 colorOut;
out vec3 fragPos;

void main() {
	gl_Position = vec4(position.x, position.y, position.z, 1.0f);

	colorOut = colorData;
	fragPos = vec3( gl_Position );
}