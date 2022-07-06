#pragma once

#include "SpriteSystem.h"

//Emitter class
class Emitter : public BaseObject {
public:
	//Physics calculations
	void integrate() {
		//Linear
		pos += linearVelocity * dt;
		linearAcceleration += force * (1 / mass);
		linearVelocity += linearAcceleration * dt;
		linearVelocity *= damping;

		//Angular
		rotation += angularVelocity * dt;
		angularVelocity *= damping;

		force = glm::vec3(0, 0, 0);
	}
	//Set functions
	void start() {
		started = true;
		lastSpawned = 0;
	}
	void stop() {
		started = false;
	}
	void setLifespan(float l) {
		lifespan = l;
	}
	void setVelocity(glm::vec3 v) {
		velocity = v;
	}
	void setChildImage(ofImage img) {
		childImage = img;
		haveChildImage = true;
	}
	void setImage(ofImage img) {
		image = img;
		width = image.getWidth();
		height = image.getHeight();
		hitBoxEmitter.width = width;
		hitBoxEmitter.height = height;
		haveImage = true;
	}
	void setRate(float r) {
		rate = r;
	}

	void setSpriteHitBox(float w, float h) {
		spriteHitBoxWidth = w;
		spriteHitBoxHeight = h;
	}

	//Draw emitter function
	void draw() {

		//Draw emitter with current transformation matrix
		ofPushMatrix();
		ofMultMatrix(getCurrentMatrix());

		if (drawable) {

			if (haveImage) {
				image.draw(-image.getWidth() / 2, -image.getHeight() / 2);
			}
			else {
				ofSetColor(0, 0, 200);
				ofDrawRectangle(-image.getWidth() / 2, -image.getHeight() / 2, width, height);
			}
		}
		//Reset sprite image for next matrix
		ofPopMatrix();

		//Call sprite system draw function
		sys->draw();
	}
	//Curve evaluation function
	glm::vec3 curveEval(float x, float s, float c)
	{
		scale = s;
		cycles = c;
		float u = (cycles * x * PI) / ofGetWidth();
		return (glm::vec3(x, -scale * sin(u) + (ofGetHeight() / 7), 0));
	}
	//Emitter moving function
	void moving() {
		if (pos.x > (ofGetWindowWidth() - 1))
			pos = curveEval(0, scale, cycles);
		heading = glm::normalize(curveEval(pos.x + 1, scale, cycles) - pos);
		glm::vec3 p = pos + heading;
		glm::vec3 newPos = curveEval(p.x, scale, cycles);
		heading = glm::normalize(newPos - pos);
		setPosition(pos + heading);
		rotation = -glm::degrees(glm::orientedAngle(heading, glm::vec3(0, -1, 0), glm::vec3(0, 0, 1)));
		spriteRotation = -glm::degrees(glm::orientedAngle(glm::vec3(0, -1, 0), glm::vec3(0, -1, 0), glm::vec3(0, 0, 1)));
	}
	//Emitter update function
	void update() {
		//If emitter hasn't started yet then return
		if (!started) return;

		float time = ofGetElapsedTimeMillis();
		//Check for sprite image
		if (shoot && (time - lastSpawned) > (1000.0 / rate)) {
			Sprite sprite;
			if (haveChildImage) {
				sprite.setSpriteImage(childImage);
			}
			//Assign values to sprite attributes
			sprite.pos = pos;
			sprite.hitBoxSprite.x = sprite.pos.x;
			sprite.hitBoxSprite.y = sprite.pos.y;
			sprite.hitBoxSprite.width = spriteHitBoxWidth;
			sprite.hitBoxSprite.height = spriteHitBoxHeight;
			sprite.rotation = spriteRotation;
			sprite.velocity = velocity;
			sprite.lifespan = lifespan * 1000;
			sprite.birthtime = time;
			//Call sprite system add function
			sys->add(sprite);
			//Assign current time as last sprite spawned 
			lastSpawned = time;
		}
		//Call sprite system update function
		sys->update();
	}
	//Emitter constructor
	Emitter(SpriteSystem *spriteSys) {
		sys = spriteSys;
	}
	//Physics data 
	glm::vec3 linearVelocity = glm::vec3(0, 0, 0);
	glm::vec3 linearAcceleration = glm::vec3(0, 0, 0);
	glm::vec3 force = glm::vec3(0, 0, 0);
	float angularVelocity = 0;
	float damping = .99;
	float mass = 1;
	float dt = 1 / ofGetFrameRate();
	//Declared variables
	SpriteSystem *sys;
	float rate = 1.0, lifespan = 0, lastSpawned;
	float spriteHitBoxWidth, spriteHitBoxHeight;
	float scale, cycles;
	glm::vec3 velocity = glm::vec3(0, 0, 0);
	bool started = false;
	ofImage image;
	ofImage childImage;
	ofSoundPlayer shootSound, collisionSound;
	bool drawable = false;
	bool haveChildImage = false;
	bool haveImage = false;
	bool shoot = false;
	bool move = false;
	float width = 0, height = 0;
	float spriteRotation;
	ofRectangle hitBoxEmitter;
};