#pragma once

#include "BaseObject.h"

//Sprite class
class Sprite : public BaseObject {
public:
	//Declare variables
	ofImage spriteImage;
	bool haveSpriteImage;
	glm::vec3 velocity;
	ofRectangle hitBoxSprite;
	float width, height, birthtime, lifespan;
	//Get age function
	float age() {
		return (ofGetElapsedTimeMillis() - birthtime);
	}
	//Set image function
	void setSpriteImage(ofImage img) {
		spriteImage = img;
		width = spriteImage.getWidth();
		height = spriteImage.getHeight();
		hitBoxSprite.width = width;
		hitBoxSprite.height = height;
		haveSpriteImage = true;
	}
	//Draw sprite function
	void draw() {

		//Draw sprite with current transformation matrix
		ofPushMatrix();
		ofMultMatrix(getCurrentMatrix());

		if (haveSpriteImage) {
			spriteImage.draw(-spriteImage.getWidth() / 2, -spriteImage.getHeight() / 2);
		}
		else {
			ofSetColor(0, 0, 200);
			ofDrawRectangle(-spriteImage.getWidth() / 2, -spriteImage.getHeight() / 2, width, height);
		}
		//Reset sprite image for next matrix
		ofPopMatrix();
	}
};