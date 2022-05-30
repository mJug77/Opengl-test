#ifndef ELEMENT_BUFFER_OBJECT_HPP
#define ELEMENT_BUFFER_OBJECT_HPP
#include <GL/glew.h>

class ElementBufferObject {
private:
	GLuint ID;
public:
	ElementBufferObject(GLuint size, void* data, GLenum usage) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	}

	void bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void del() {
		glDeleteBuffers(1, &ID);
	}
};

#endif