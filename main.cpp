#define WIDTH 640
#define HEIGHT 480

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "VertexBufferObject.hpp"
#include "ElementBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include "Texture.hpp"
#include "Shader.hpp"


GLfloat vertices[] = {
	 // POSITIONS        // RGB              //TEXTURE COORDINATES
	 0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
	 0.5f,-0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	-0.5f,-0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 1.0f,   0.0f, 1.0f
};

GLuint indices[] = {
	0, 1, 3,
	1, 2, 3
};

int main() {
	// WINDOW
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

	// SHADER PROGRAM
	Shader shader1("Vertex.glsl", "Fragment.glsl");

	// BUFFERS
	VertexArrayObject   vao1;
	VertexBufferObject  vbo1(sizeof(vertices), &vertices, GL_STATIC_DRAW);
	ElementBufferObject ebo1(sizeof(indices), &indices, GL_STATIC_DRAW);
	vao1.bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// TEXTURES
	Texture texture1(GL_TEXTURE_2D, "res/container.jpg");
	Texture texture2(GL_TEXTURE_2D, "res/awesomeface.png");

	shader1.enable();
	
	glUniform1i(glGetUniformLocation(shader1.ID, "tex0"), 0);
	glUniform1i(glGetUniformLocation(shader1.ID, "tex1"), 1);

	// MATH
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 0.0f);
	glm::mat4 trans(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0f, 0.0f, 0.0f));
	vec = trans * vec;

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);

		// render
		shader1.enable();

		glActiveTexture(GL_TEXTURE0);
		texture1.bind(GL_TEXTURE_2D);

		glActiveTexture(GL_TEXTURE1);
		texture2.bind(GL_TEXTURE_2D);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &indices);

		// events
		glfwPollEvents();
	}

	shader1.del();
	vao1.del();
	vbo1.del();
	ebo1.del();
	texture1.del();

	glfwTerminate();
	return EXIT_SUCCESS;
}
