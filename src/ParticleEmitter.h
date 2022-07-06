#pragma once

//  Kevin M. Smith - CS 134 SJSU

#include "ParticleSystem.h"

typedef enum { DirectionalEmitter, RadialEmitter, SphereEmitter } EmitterType;

class ParticleEmitter : public BaseObject {
public:
	void setLifespan(const float life) { lifespan = life; }
	void setVelocity(const ofVec3f &vel) { velocity = vel; }
	void setRate(const float r) { rate = r; }
	void setParticleRadius(const float r) { particleRadius = r; }
	void setEmitterType(EmitterType t) { type = t; }
	void setGroupSize(int s) { groupSize = s; }
	void setOneShot(bool s) { oneShot = s; }
	ParticleSystem *sys;
	float rate;         // per sec
	bool oneShot;
	bool fired;
	ofVec3f velocity;
	float lifespan;     // sec
	bool started;
	float lastSpawned;  // ms
	float particleRadius;
	float radius;
	bool visible;
	int groupSize;      // number of particles to spawn in a group
	bool createdSys;
	EmitterType type;
	ParticleEmitter() {
		sys = new ParticleSystem();
		createdSys = true;
		init();
	}

	ParticleEmitter(ParticleSystem *s) {
		if (s == NULL)
		{
			cout << "fatal error: null particle system passed to ParticleEmitter()" << endl;
			ofExit();
		}
		sys = s;
		createdSys = false;
		init();
	}

	~ParticleEmitter() {

		// deallocate particle system if emitter created one internally
		//
		if (createdSys) delete sys;
	}

	void init() {
		rate = 1;
		velocity = ofVec3f(0, 20, 0);
		lifespan = 3;
		started = false;
		oneShot = false;
		fired = false;
		lastSpawned = 0;
		radius = 1;
		particleRadius = .1;
		visible = true;
		type = DirectionalEmitter;
		groupSize = 1;
	}

	void draw() {
		if (visible) {
			switch (type) {
			case DirectionalEmitter:
				ofDrawSphere(pos, radius / 10);  // just draw a small sphere for point emitters 
				break;
			case SphereEmitter:
			case RadialEmitter:
				ofDrawSphere(pos, radius / 50);  // just draw a small sphere as a placeholder
				break;
			default:
				break;
			}
		}
		sys->draw();
	}
	void start() {
		started = true;
		lastSpawned = ofGetElapsedTimeMillis();
	}

	void stop() {
		started = false;
		fired = false;
	}
	void update() {

		float time = ofGetElapsedTimeMillis();

		if (oneShot && started) {
			if (!fired) {

				// spawn a new particle(s)
				//
				for (int i = 0; i < groupSize; i++)
					spawn(time);

				lastSpawned = time;
			}
			fired = true;
			stop();
		}

		else if (((time - lastSpawned) > (1000.0 / rate)) && started) {

			// spawn a new particle(s)
			//
			for (int i = 0; i < groupSize; i++)
				spawn(time);

			lastSpawned = time;
		}

		sys->update();
	}

	// spawn a single particle.  time is current time of birth
	//
	void spawn(float time) {

		Particle particle;

		// set initial velocity and position
		// based on emitter type
		//
		switch (type) {
		case RadialEmitter:
		{
			ofVec3f dir = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
			float speed = velocity.length();
			particle.velocity = dir.getNormalized() * speed;
			particle.position.set(pos);
		}
		break;
		case SphereEmitter:
			break;
		case DirectionalEmitter:
			particle.velocity = velocity;
			particle.position.set(pos);
			break;
		}

		// other particle attributes
		//
		particle.lifespan = lifespan;
		particle.birthtime = time;
		particle.radius = particleRadius;

		// add to system
		//
		sys->add(particle);
	}

};
