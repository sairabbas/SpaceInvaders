#pragma once

#include "ofMain.h"

//Base object class
class BaseObject {
public:
	//Declare variables
	float rotation;
	glm::vec3 pos, heading, boundary, scale;
	glm::mat4 trans, rot;
	//Set position function
	void setPosition(glm::vec3 p) {
		pos = p;
	}
	//Set scale function
	void setScale(float s) {
		scale = glm::vec3(s, s, s);
	}
	//Base object constructor
	BaseObject::BaseObject() {
		rotation = 0.0;
		pos = glm::vec3(0, 0, 0);
		scale = glm::vec3(1, 1, 1);
		trans = glm::translate(glm::mat4(1.0), glm::vec3(pos));
		rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
		heading = rot * glm::vec4(0, 1, 0, 0);
	}
	//Get current transformation matrix function
	glm::mat4 getCurrentMatrix() {
		glm::mat4 t = glm::translate(glm::mat4(1.0), glm::vec3(pos));
		glm::mat4 r = glm::rotate(t, glm::radians(rotation), glm::vec3(0, 0, 1));
		glm::mat4 M = glm::scale(r, scale);
		return M;
	}
};