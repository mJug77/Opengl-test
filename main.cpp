#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <iostream>

#include "VertexBufferObject.hpp"
#include "ElementBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include "Texture.hpp"
#include "Shader.hpp"



float vertices[] = {
	// positions          // texture coords
	 100.5f,  100.5f, 0.0f,   1.0f, 1.0f, // top right
	 100.5f, -100.5f, 0.0f,   1.0f, 0.0f, // bottom right
	-100.5f, -100.5f, 0.0f,   0.0f, 0.0f, // bottom left
	-100.5f,  100.5f, 0.0f,   0.0f, 1.0f  // top left 
};

GLuint indices[] = {
	0, 1, 3,
	1, 2, 3
};

int main() {
	// WINDOW
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", NULL, NULL);

	int x = 800, y = 600;

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

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// SHADER PROGRAM
	Shader shader1("Vertex.glsl", "Fragment.glsl");

	// BUFFERS
	VertexArrayObject   vao1;
	VertexBufferObject  vbo1(sizeof(vertices), &vertices, GL_STATIC_DRAW);
	ElementBufferObject ebo1(sizeof(indices), &indices, GL_STATIC_DRAW);
	vao1.bind();

	// ATTRIBUTES
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// TEXTURES
	Texture texture1(GL_TEXTURE_2D, "res/container.jpg");
	Texture texture2(GL_TEXTURE_2D, "res/awesomeface.png");

	shader1.enable();
	
	shader1.setUniformInt("tex0", 0);
	shader1.setUniformInt("tex1", 1);
	
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		// MATH
		glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 100.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(100, 0.0f, 0.0f));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(500, 100.0f, 0.0f));

		glm::mat4 mvp = proj * view * model;

		// render
		shader1.enable();

		glActiveTexture(GL_TEXTURE0);
		texture1.bind(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE1);
		texture2.bind(GL_TEXTURE_2D);

		shader1.setUniformMat4f("proj", mvp);

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