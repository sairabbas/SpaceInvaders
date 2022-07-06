#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Emitter.h"
#include "ParticleEmitter.h"

//ofApp class
class ofApp : public ofBaseApp{
	//Declared functions
	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void checkCollisions();
		//Declared variables
		vector<Emitter *> emitters;
		Emitter *turret = NULL;
		Emitter *enemyShip1 = NULL;
		Emitter *enemyShip2 = NULL;
		Emitter *enemyShip3 = NULL;
		Emitter *enemyShip4 = NULL;
		Emitter *enemyShip5 = NULL;
		ParticleEmitter radialEmitter;
		TurbulenceForce *turbForce;
		GravityForce *gravityForce;
		ImpulseRadialForce *radialForce;
		ofImage backgroundImage;
		ofSoundPlayer music;
		ofTrueTypeFont gameFont, scoreFont;
		bool imageLoaded;
		bool bHide;
		bool gameOver = false;
		int score = 0;
		int emittersAlive;
		ofxPanel gui;
};
