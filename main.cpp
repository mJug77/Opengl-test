#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexBufferObject.hpp"
#include "ElementBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include "Shader.hpp"

#define WIDTH 640
#define HEIGHT 480

GLfloat vertices[] = {
	 -0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
	  0.0f,  0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
	  0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f,
};

GLuint indices[] = {
	0, 1, 2,
	2, 3, 0,
};

int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Window", NULL, NULL);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(window);
	glfwSetWindowAttrib(window, GLFW_RESIZABLE, false);

	GLenum err = glewInit();
	if (GLEW_OK != err) { 
		std::cout << "Something is seriously wrong dumbass" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glViewport(0, 0, WIDTH, HEIGHT);
	
	VertexBufferObject vbo1(sizeof(vertices), &vertices, GL_STATIC_DRAW);
	ElementBufferObject ebo1(sizeof(indices), &indices, GL_STATIC_DRAW);

	VertexArrayObject vao1;
	vao1.setAttributes(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0 * sizeof(float));
	vao1.setAttributes(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float));
	vao1.enable(0);
	vao1.enable(1);

	Shader shader1("Vertex.glsl", "Fragment.glsl");
	shader1.enable();

	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window)) {
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, &indices);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}