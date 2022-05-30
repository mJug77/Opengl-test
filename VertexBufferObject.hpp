#ifndef VERTEX_BUFFER_OBJECT_HPP
#define VERTEX_BUFFER_OBJECT_HPP
#include <GL/glew.h>

class VertexBufferObject {
private:
	GLuint ID;
public:
	VertexBufferObject(GLuint size, void* data, GLenum usage) {
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	}

	void bind() {
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void del() {
		glDeleteBuffers(1, &ID);
	}
};
#endif