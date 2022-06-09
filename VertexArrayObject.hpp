#ifndef VERTEX_ARRAY_OBJECT_HPP
#define VERTEX_ARRAY_OBJECT_HPP
#include <GL/glew.h>

class VertexArrayObject {
public:
	GLuint ID;

	VertexArrayObject() {
		glGenVertexArrays(1, &ID);
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
};
#endif