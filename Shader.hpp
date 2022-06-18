#ifndef SHADER_HPP
#define SHADER_HPP
#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


class Shader {
private:
	GLint  success;
	GLuint VertexID;
	GLuint FragmentID;

	std::string getFile(const std::string PATH) {
		std::ifstream file;
		std::stringstream buffer;
		std::string data;

		file.open(PATH);
		buffer << file.rdbuf();
		data = buffer.str();
		
		file.close();

		return data;
	}
public:
	GLuint ID;

	Shader(const std::string vertPath, const std::string fragPath) {
		ID = glCreateProgram();
		VertexID   = glCreateShader(GL_VERTEX_SHADER);
		FragmentID = glCreateShader(GL_FRAGMENT_SHADER);

		std::string v = getFile(vertPath);
		std::string f = getFile(fragPath);

		const char* vertexSource   = v.c_str();
		const char* fragmentSource = f.c_str();

		glShaderSource(VertexID, 1, &vertexSource, nullptr);
		glShaderSource(FragmentID, 1, &fragmentSource, nullptr);

		glCompileShader(VertexID);
		glCompileShader(FragmentID);

		glGetShaderiv(VertexID, GL_COMPILE_STATUS, &success);
		if (!success) {
			int maxLength = 0;
			char infoLog[510];
			glGetShaderiv(VertexID, GL_INFO_LOG_LENGTH, &maxLength);
			glGetShaderInfoLog(VertexID, maxLength, &maxLength, infoLog);

			std::cout << "VSHADER COMPILATION FAILED: " << infoLog << std::endl;
		}

		glGetShaderiv(FragmentID, GL_COMPILE_STATUS, &success);
		if (!success) {
			int maxLength = 0;
			char infoLog[510];
			glGetShaderiv(VertexID, GL_INFO_LOG_LENGTH, &maxLength);
			glGetShaderInfoLog(VertexID, maxLength, &maxLength, infoLog);

			std::cout << "FSHADER COMPILATION FAILED: " << infoLog << std::endl;
		}

		glAttachShader(ID, VertexID);
		glAttachShader(ID, FragmentID);
		glLinkProgram(ID);
	}

	void setUniformInt(const char* var_name, GLint value) {
		glUniform1i(glGetUniformLocation(ID, var_name), value);
	}

	void setUniformFloat(const char* var_name, GLfloat value) {
		glUniform1f(glGetUniformLocation(ID, var_name), value);
	}

	void setUniformMat4f(const char* var_name, glm::mat4 matrix) {
		glUniformMatrix4fv(glGetUniformLocation(ID, var_name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void enable() {
		glUseProgram(ID);
		glDeleteShader(VertexID);
		glDeleteShader(FragmentID);
	}

	void disable() {
		glUseProgram(0);
	}

	void del() {
		glDeleteProgram(ID);
	}
};

#endif