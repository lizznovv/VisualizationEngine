#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Lamprey {

public:

	int N = 10;
	float length = 1.0f;

	std::vector<float> angles;

	Lamprey(int n) : N(n) {
		angles.resize(N, 0.0f);
	}

	void update(float time) {
		for (int i = 0; i < N; i++) {
			angles[i] = 0.7f * cos(time * 5.0f + i * 0.1f); // вместо CPG пока
		}
	}
	void drawSegments(GLuint modelLoc) {

		//все сегменты - это один объект
		glm::mat4 model(1.0f);

		for (int i = 0; i < N; i++)
		{
			model = model * glm::rotate(glm::mat4(1.0f), glm::radians(angles[i]), glm::vec3(0, 0, 1));
			model = model * glm::translate(glm::mat4(1.0f), glm::vec3(length, 0, 0));

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

};