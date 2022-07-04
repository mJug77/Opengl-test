#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.hpp"

class Camera {
public:
	glm::vec3 position;
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	int height, width;
	float speed = 0.001f, sensitivity = 50.0f;

	Camera(int width, int height, glm::vec3 position) {
		Camera::width = width;
		Camera::height = height;
		Camera::position = position;
	}

	void matrix(float FOVdeg, float near, float far, Shader& shader, const char* uniform) {
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		view = glm::lookAt(position, position + orientation, up);
		proj = glm::perspective(glm::radians(FOVdeg), (float)(width / height), near, far);

		shader.setUniformMat4f(uniform, proj * view);
	}

	void input(GLFWwindow* window) {
		// KEYBOARD
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			position += speed * orientation;
		}
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			position += speed * -glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			position += speed * -orientation;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			position += speed * glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			position += speed * up;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			position += speed * -up;
		}

		// MOUSE
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);

			float rotationX = sensitivity * (float)(mouseY - (height / 2)) / height;
			float rotationY = sensitivity * (float)(mouseX - (width / 2)) / width;

			glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotationX), glm::normalize(glm::cross(orientation, up)));

			// clamp vertical rotation
			if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f)) {
				orientation = newOrientation;
			}

			orientation = glm::rotate(orientation, glm::radians(-rotationY), up);
			glfwSetCursorPos(window, (width / 2), (height / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
};

#endif