#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

uniform float scale;

void main() {
	gl_Position = proj * view * model * vec4(aPos, scale);
	TexCoord = aTexCoord;
}