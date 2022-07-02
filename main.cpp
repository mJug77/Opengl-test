#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexBufferObject.hpp"
#include "ElementBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include "Texture.hpp"
#include "Shader.hpp"


GLfloat vertices[] = { 
	// COORDINATES          // TexCoord
	-0.5f, 0.0f,  0.5f, 	1.0f, 1.0f,
	-0.5f, 0.0f, -0.5f, 	1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f, 	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f, 	0.0f, 1.0f,
	 0.0f, 0.8f,  0.0f, 	1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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

	// IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// VARS
	float scale = 0.50f;
	float X = 0.0f, Y = 0.0f;

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		// TIME
		double currTime = glfwGetTime();
		if (currTime - prevTime >= 1 / 60) {
			rotation += 0.05f;
			prevTime = currTime;
		}

		// MATH
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view  = glm::mat4(1.0f);
		glm::mat4 proj  = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), float(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 100.0f);


		//glm::mat4 mvp = proj * view * model;

		// render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		shader1.enable();

		glActiveTexture(GL_TEXTURE0);
		texture1.bind(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE1);
		texture2.bind(GL_TEXTURE_2D);

		shader1.setUniformMat4f("proj", proj);
		shader1.setUniformMat4f("view", view);
		shader1.setUniformMat4f("model", model);
		shader1.setUniformFloat("scale", scale);

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, &indices);

		ImGui::Begin("I'm gui window");
			ImGui::Text("Hello, World!");
			ImGui::SliderFloat("Scale", &scale, 0.0f, 100.0f);
			ImGui::SliderFloat("X", &X, 0.0f, 600.0f);
			ImGui::SliderFloat("Y", &Y, 0.0f, 800.0f);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// events
		glfwPollEvents();
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	shader1.del();
	vao1.del();
	vbo1.del();
	ebo1.del();
	texture1.del();

	glfwTerminate();
	return EXIT_SUCCESS;
}