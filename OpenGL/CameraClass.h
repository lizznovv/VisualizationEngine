#pragma once

// Std. Includes
#include <vector>

// GL Includes
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera {
public:

	glm::mat4 GetViewMatrix() {
		return glm::lookAt(this->cameraPos, this->cameraPos + this->cameraFront, this->cameraUp);
	}

	glm::vec3 GetCameraPos() {
		return cameraPos;
	}

	GLfloat GetFov() {
		return fov;
	}

	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset) {
		
		xoffset *= this->sensitivity;
		yoffset *= this->sensitivity;

		this->yaw += xoffset;
		this->pitch += yoffset;

		if (this->pitch > 89.0f)
			this->pitch = 89.0f;
		if (this->pitch < -89.0f)
			this->pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		front.y = sin(glm::radians(this->pitch));
		front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		this->cameraFront = glm::normalize(front);
	}
	
	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
		
		GLfloat cameraSpeed = this->speed * deltaTime;
		if (direction == FORWARD)
			this->cameraPos += this->cameraFront * cameraSpeed;
		if (direction == BACKWARD)
			this->cameraPos -= this->cameraFront * cameraSpeed;
		if (direction == LEFT)
			this->cameraPos -= glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * cameraSpeed;
		if (direction == RIGHT)
			this->cameraPos += glm::normalize(glm::cross(this->cameraFront, this->cameraUp)) * cameraSpeed;
		if (direction == UP)
			this->cameraPos += this->cameraUp * cameraSpeed;
		if (direction == DOWN)
			this->cameraPos -= this->cameraUp * cameraSpeed;

	}
	void ProcessMouseScroll(double yoffset) {
		if (this->fov >= 1.0f && this->fov <= 45.0f)
			this->fov -= yoffset;
		if (this->fov <= 1.0f)
			this->fov = 1.0f;
		if (this->fov >= 45.0f)
			this->fov = 45.0f;
	}

private:
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	GLfloat yaw = -90.0f;
	GLfloat pitch = 0.0f;

	GLfloat speed = 5.0f;
	GLfloat sensitivity = 0.05;
	GLfloat fov = 45.0f;

};