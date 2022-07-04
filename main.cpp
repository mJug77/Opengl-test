#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>
*/

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexBufferObject.hpp"
#include "ElementBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include "Shader.hpp"
#include "Camera.hpp"


GLfloat vertices[] = { 
	// COORDINATES          // COLOR
	-0.5f, 0.0f,  0.5f, 	1.0f, 0.0f, 0.0f, 
	-0.5f, 0.0f, -0.5f, 	0.0f, 1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f, 	0.0f, 0.0f, 1.0f,
	 0.5f, 0.0f,  0.5f, 	1.0f, 1.0f, 0.0f,
	 0.0f, 1.0f,  0.0f, 	0.0f, 1.0f, 1.0f
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

	//int x = 800, y = 600;

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	shader1.enable();

	/*
	// IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	*/

	// CAMERA
	Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 0.2f));

	// VAR
	float scale = 0.50f;
	float x_position = 0.0f;
	float y_position = 0.0f;

	glEnable(GL_DEPTH_TEST);


	// MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);

		// TIME
		double currTime = glfwGetTime();


		// RENDER
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		*/

		shader1.enable();

		camera.matrix(45, 0.1f, 100.0f, shader1, "cameraMatrix");
		camera.input(window);

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, &indices);

		/*
		// IMGUI
		ImGui::Begin("I'm gui window");
			ImGui::Text("Hello, World!");
			ImGui::SliderFloat("X position", &x_position, -400, 400);
			ImGui::SliderFloat("Y position", &y_position, -300, 300);
			ImGui::SliderFloat("Scale", &scale, 0, 10);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		*/

		// EVENTS
		glfwPollEvents();
	}

	// TERMINATION
	/*
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	*/
	shader1.del();
	vao1.del();
	vbo1.del();
	ebo1.del();

	glfwTerminate();
	return EXIT_SUCCESS;
}