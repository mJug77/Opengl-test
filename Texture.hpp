#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <iostream>
#include "STB/stb_image.h"

class Texture {
public:
	GLuint ID;
	Texture(GLenum target, const char* filePath) {
		glGenTextures(1, &ID);
		glBindTexture(target, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filePath, &width, &height, &channels, 4);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Error opening file!" << std::endl;
		}
		stbi_image_free(data);
	}

	void bind(GLenum target) {
		glBindTexture(target, ID);
	}

	void unbind(GLenum target) {
		glBindTexture(target, 0);
	}

	void del() {
		glDeleteTextures(1, &ID);
	}
};

#endif