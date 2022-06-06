#version 330 core

in vec3 outputColor;
out vec4 aColor;

void main() {
	aColor = vec4(outputColor, 1.0f);
}