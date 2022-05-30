#ifndef VERTEX_ARRAY_OBJECT_HPP
#define VERTEX_ARRAY_OBJECT_HPP
#include <GL/glew.h>

class VertexArrayObject {
private:
	GLuint ID;
public:
	VertexArrayObject(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset) {
		glGenVertexArrays(1, &ID);
		glBindVertexArray(ID);
		glVertexAttribPointer(index, size, type, normalized, stride, (void*)offset);
	}

	void bind() {
		glBindVertexArray(ID);
	}

	void unbind() {
		glBindVertexArray(0);
	}

	void del() {
		glDeleteVertexArrays(1, &ID);
	}

	void enable(GLuint index) {
		glEnableVertexAttribArray(index);
	}
};
#endif