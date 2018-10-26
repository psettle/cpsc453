#version 330 core

#define LINE_VERTEX_COUNT 50

layout (lines_adjacency) in;
layout (line_strip, max_vertices = LINE_VERTEX_COUNT) out;

void main() {

	vec4 P0 = gl_in[0].gl_Position;
	vec4 P1 = gl_in[1].gl_Position;
	vec4 P2 = gl_in[2].gl_Position;
	vec4 P3 = gl_in[3].gl_Position;

	for (int i = 0; i < LINE_VERTEX_COUNT; ++i)
    {
        float t = i / float(LINE_VERTEX_COUNT - 1);
        gl_Position = (1 - t) * (1 - t) * (1 - t) * P0 + 3 * (1 - t) * (1 - t) * t * P1 + 3 * (1 - t) * t * t * P2 + t * t * t * P3;
		EmitVertex();
    }

    EndPrimitive();
}  