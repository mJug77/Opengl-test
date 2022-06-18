#version 330 core

out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D tex0;
uniform sampler2D tex1;

void main() {
	FragColor = mix(texture(tex0, TexCoord), texture(tex1, TexCoord), 0.2f);
}