#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include "Shader.hpp"

GLfloat vertices[] = {
	 0.5f, 0.0f, 0.0f,
	-0.5f, 0.0f, 0.0f,
	 0.0f, 0.5f, 0.0f
};

int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(800, 800, "Window", NULL, NULL);

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
	glViewport(0, 0, 800, 600);
	
	VertexBufferObject vbo1(6 * sizeof(vertices), &vertices, GL_STATIC_DRAW);
	VertexArrayObject vao1(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	vao1.enable(0);

	Shader shader1("Vertex.glsl", "Fragment.glsl");
	shader1.enable();

	while (!glfwWindowShouldClose(window)) {
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}