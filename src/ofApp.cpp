#include "ofApp.h"

//Check for collisions function
void ofApp::checkCollisions() {
	if (emittersAlive > 1)
	{
		for (int i = 1; i < emitters.size(); i++)
		{
			//Check if turret sprite collides with enemy emitter
			if (turret->sys->sprites.size() > 0)
			{
				for (int j = 0; j < turret->sys->sprites.size(); j++)
				{
					if (turret->sys->sprites[j].hitBoxSprite.intersects(emitters[i]->hitBoxEmitter))
					{
						//Update how many emitters alive
						emittersAlive -= 1;
						//Draw explosion
						radialEmitter.setPosition(emitters[i]->pos);
						radialEmitter.sys->reset();
						radialEmitter.start();
						//Destroy enemy emitter
						emitters[i]->shoot = false;
						emitters[i]->move = false;
						emitters[i]->setPosition(glm::vec3(-100, -100, 0));
						turret->sys->sprites[j].lifespan = 0;
						turret->collisionSound.play();
						//Update score
						score += 10;
					}
				}
			}
			//Check if turret sprite collides with enemy emitter sprites
			if (turret->sys->sprites.size() > 0 && emitters[i]->sys->sprites.size() > 0)
			{
				for (int j = 0; j < turret->sys->sprites.size(); j++)
				{
					for (int k = 0; k < emitters[i]->sys->sprites.size(); k++)
					{
						if (turret->sys->sprites[j].hitBoxSprite.intersects(emitters[i]->sys->sprites[k].hitBoxSprite))
						{
							//Collision explosion
							radialEmitter.setPosition(emitters[i]->sys->sprites[k].pos);
							radialEmitter.sys->reset();
							radialEmitter.start();
							//Destroy enemy sprite
							emitters[i]->sys->sprites[k].lifespan = 0;
							turret->sys->sprites[j].lifespan = 0;
							turret->collisionSound.play();
							//Update score
							score += 1;
						}
					}
				}
			}
			//Check if enemy emitter collides with turret
			if (emitters[i]->hitBoxEmitter.intersects(turret->hitBoxEmitter))
			{
				//Collision explosion
				radialEmitter.setPosition(turret->pos);
				radialEmitter.sys->reset();
				radialEmitter.start();
				//End game
				turret->stop();
				turret->collisionSound.play();
				gameOver = true;
			}
			//Check if enemy sprites collides with turret
			if (emitters[i]->sys->sprites.size() > 0)
			{
				for (int j = 0; j < emitters[i]->sys->sprites.size(); j++)
				{
					if (emitters[i]->sys->sprites[j].hitBoxSprite.intersects(turret->hitBoxEmitter))
					{
						//Collision explosion
						radialEmitter.setPosition(turret->pos);
						radialEmitter.sys->reset();
						radialEmitter.start();
						//End game
						turret->stop();
						turret->collisionSound.play();
						gameOver = true;
					}
				}
			}
		}
	}
	//End game
	else
	{
		turret->stop();
		gameOver = true;
	}
}

//--------------------------------------------------------------
//Set up game function 
void ofApp::setup(){
	ofSetVerticalSync(true);
	//Initialize score font
	scoreFont.load("fonts/font2.ttf", 40);
	//Initialize music
	music.load("sounds/music.ogg");
	music.setVolume(0.3);
	music.play();
	music.setLoop(true);
	//Initialize background image
	backgroundImage.load("images/space.jpg");
	//Initialize player turret
	turret = new Emitter(new SpriteSystem());
	turret->pos = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() - ofGetWindowHeight() / 8.0, 0);
	turret->rate = 5;
	turret->lifespan = 5;
	turret->setImage(ofImage("images/turret.png"));
	turret->setChildImage(ofImage("images/missile.png"));
	turret->hitBoxEmitter.width = 100;
	turret->hitBoxEmitter.height = 100;
	turret->setSpriteHitBox(30, 75);
	turret->shootSound.load("sounds/shoot.wav");
	turret->shootSound.setVolume(0.2);
	turret->collisionSound.load("sounds/explode.wav");
	turret->collisionSound.setVolume(0.2);
	turret->shoot = false;
	turret->move = false;
	turret->drawable = true;
	emitters.push_back(turret);
	//Initialize enemy emitter1
	enemyShip1 = new Emitter(new SpriteSystem());
	enemyShip1->pos = enemyShip1->curveEval(0, 0, 0);
	enemyShip1->velocity = glm::vec3(0, 100, 0);
	enemyShip1->rate = 2;
	enemyShip1->lifespan = 10;
	enemyShip1->setImage(ofImage("images/enemyship.png"));
	enemyShip1->setChildImage(ofImage("images/mySprite.png"));
	enemyShip1->hitBoxEmitter.width = 70;
	enemyShip1->hitBoxEmitter.height = 70;
	enemyShip1->setSpriteHitBox(40, 40);
	enemyShip1->shoot = true;
	enemyShip1->move = true;
	enemyShip1->drawable = true;
	enemyShip1->start();
	emitters.push_back(enemyShip1);
	//Initialize enemy emitter2
	enemyShip2 = new Emitter(new SpriteSystem());
	enemyShip2->pos = enemyShip2->curveEval(0, 50, 5);
	enemyShip2->velocity = glm::vec3(0, 100, 0);
	enemyShip2->rate = 2;
	enemyShip2->lifespan = 10;
	enemyShip2->setImage(ofImage("images/enemyship.png"));
	enemyShip2->setChildImage(ofImage("images/mySprite.png"));
	enemyShip2->hitBoxEmitter.width = 70;
	enemyShip2->hitBoxEmitter.height = 70;
	enemyShip2->setSpriteHitBox(40, 40);
	enemyShip2->shoot = true;
	enemyShip2->move = true;
	enemyShip2->drawable = true;
	enemyShip2->start();
	emitters.push_back(enemyShip2);
	//Initialize enemy emitter3
	enemyShip3 = new Emitter(new SpriteSystem());
	enemyShip3->pos = enemyShip3->curveEval(0, 100, 10);
	enemyShip3->velocity = glm::vec3(0, 100, 0);
	enemyShip3->rate = 2;
	enemyShip3->lifespan = 10;
	enemyShip3->setImage(ofImage("images/enemyship.png"));
	enemyShip3->setChildImage(ofImage("images/mySprite.png"));
	enemyShip3->hitBoxEmitter.width = 70;
	enemyShip3->hitBoxEmitter.height = 70;
	enemyShip3->setSpriteHitBox(40, 40);
	enemyShip3->shoot = true;
	enemyShip3->move = true;
	enemyShip3->drawable = true;
	enemyShip3->start();
	emitters.push_back(enemyShip3);
	//Initialize enemy emitter4
	enemyShip4 = new Emitter(new SpriteSystem());
	enemyShip4->pos = enemyShip4->curveEval(0, 125, 8);
	enemyShip4->velocity = glm::vec3(0, 100, 0);
	enemyShip4->rate = 2;
	enemyShip4->lifespan = 10;
	enemyShip4->setImage(ofImage("images/enemyship.png"));
	enemyShip4->setChildImage(ofImage("images/mySprite.png"));
	enemyShip4->hitBoxEmitter.width = 70;
	enemyShip4->hitBoxEmitter.height = 70;
	enemyShip4->setSpriteHitBox(40, 40);
	enemyShip4->shoot = true;
	enemyShip4->move = true;
	enemyShip4->drawable = true;
	enemyShip4->start();
	emitters.push_back(enemyShip4);
	//Initialize enemy emitter5
	enemyShip5 = new Emitter(new SpriteSystem());
	enemyShip5->pos = enemyShip5->curveEval(0, 150, 2);
	enemyShip5->velocity = glm::vec3(0, 100, 0);
	enemyShip5->rate = 2;
	enemyShip5->lifespan = 10;
	enemyShip5->setImage(ofImage("images/enemyship.png"));
	enemyShip5->setChildImage(ofImage("images/mySprite.png"));
	enemyShip5->hitBoxEmitter.width = 70;
	enemyShip5->hitBoxEmitter.height = 70;
	enemyShip5->setSpriteHitBox(40, 40);
	enemyShip5->shoot = true;
	enemyShip5->move = true;
	enemyShip5->drawable = true;
	enemyShip5->start();
	emitters.push_back(enemyShip5);
	//Initialize how many emitters alive
	emittersAlive = emitters.size();
	//Initialize particle emitter for explosions
	turbForce = new TurbulenceForce(ofVec3f(-20, -20, -20), ofVec3f(20, 20, 20));
	gravityForce = new GravityForce(ofVec3f(0, -20, 0));
	radialForce = new ImpulseRadialForce(1000.0);
	radialForce->setHeight(0.01);
	radialEmitter.sys->addForce(turbForce);
	radialEmitter.sys->addForce(gravityForce);
	radialEmitter.sys->addForce(radialForce);
	radialEmitter.setVelocity(glm::vec3(200, 200, 0));
	radialEmitter.setLifespan(1);
	radialEmitter.setParticleRadius(3);
	radialEmitter.setOneShot(true);
	radialEmitter.setEmitterType(RadialEmitter);
	radialEmitter.setGroupSize(50);
}

//--------------------------------------------------------------
//Update game function
void ofApp::update() {

	//If game started update game
	if (turret->started == true)
	{
		//Assign turret sprite the same rotation as turret
		turret->setVelocity(-700 * turret->heading);
		turret->integrate();
		//Iterate and update each emitter
		for (int i = 0; i < emitters.size(); i++)
		{
			emitters[i]->setPosition(emitters[i]->pos);
			emitters[i]->hitBoxEmitter.x = emitters[i]->pos.x;
			emitters[i]->hitBoxEmitter.y = emitters[i]->pos.y;
			emitters[i]->rotation = emitters[i]->rotation;
			emitters[i]->trans = glm::translate(glm::mat4(1), glm::vec3(emitters[i]->pos));
			emitters[i]->rot = glm::rotate(glm::mat4(1), glm::radians(emitters[i]->rotation), glm::vec3(0, 0, 1));
			emitters[i]->heading = emitters[i]->getCurrentMatrix() * glm::vec4(0, 1, 0, 0);
			emitters[i]->boundary = emitters[i]->getCurrentMatrix() * glm::vec4(1);
			emitters[i]->spriteRotation = emitters[i]->rotation;
			emitters[i]->setRate(emitters[i]->rate);
			emitters[i]->setVelocity(emitters[i]->velocity);
			emitters[i]->setLifespan(emitters[i]->lifespan);
			//Check if emitter can move
			if (emitters[i]->move == true)
			{
				//Move emitter
				emitters[i]->moving();
			}
			emitters[i]->update();
		}
		//Call function to check for collisions
		checkCollisions();
		//Update explosions
		radialEmitter.update();
	}
}

//--------------------------------------------------------------
//Draw game function
void ofApp::draw() {
	
	//Draw start game image
	if (turret->started == false)
	{
		backgroundImage.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
		gameFont.load("fonts/font1.ttf", 70);
		gameFont.drawString("Armageddon", 150, ofGetWindowHeight() / 3);
		gameFont.load("fonts/font1.ttf", 30);
		gameFont.drawString("Press Spacebar to continue", 150, ofGetWindowHeight() / 2 + 100);
	}
	//If game has started draw the game
	else if (turret->started == true)
	{
		//Draw background game image
		backgroundImage.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
		//Draw each emitter
		for (int i = 0; i < emitters.size(); i++)
		{
			emitters[i]->draw();
		}
		//Draw explosion
		radialEmitter.sys->draw();
		//Draw Score
		scoreFont.drawString("Score " + to_string(score), 15, 50);
		//Check to draw GUI
		if (!bHide) {
			gui.draw();
		}
	}
	//If game is over draw game over image
	if (gameOver == true)
	{
		backgroundImage.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
		gameFont.load("fonts/font1.ttf", 70);
		gameFont.drawString("Game Over", 200, ofGetWindowHeight() / 3);
		scoreFont.load("fonts/font2.ttf", 75);
		scoreFont.drawString("Final Score " + to_string(score), 400, ofGetWindowHeight() / 2 + 100);
	}
}
//--------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	//Drag turret player with mouse
	if (x < ofGetWindowWidth() && y < ofGetWindowHeight() && x > 0 && y > 0)
	{
		turret->pos.x = x;
		turret->pos.y = y;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

void ofApp::keyPressed(int key) {
	switch (key) {
	case 'F':
	case 'f':
		ofToggleFullscreen();
		break;
	case 'H':
	case 'h':
		bHide = !bHide;
		break;
	//Check boundaries of turret player to move up
	case 'w':
	case OF_KEY_UP:
		if (turret->boundary.x < ofGetWindowWidth() && turret->boundary.y < ofGetWindowHeight() && turret->boundary.x > 0 && turret->boundary.y > 0)
			turret->linearVelocity -= turret->heading * 25;
		else if(turret->boundary.y > ofGetWindowHeight())
			turret->setPosition(glm::vec3(turret->boundary.x, turret->boundary.y - 55, 1));
		else if (turret->boundary.y < 0)
			turret->setPosition(glm::vec3(turret->boundary.x, turret->boundary.y + 55, 1));
		else if (turret->boundary.x > ofGetWindowWidth())
			turret->setPosition(glm::vec3(turret->boundary.x - 55, turret->boundary.y, 1));
		else if (turret->boundary.x < 0)
			turret->setPosition(glm::vec3(turret->boundary.x + 55, turret->boundary.y, 1));
		break;
	//Check boundaries of turret player to move down
	case 's':
	case OF_KEY_DOWN:
		if (turret->boundary.x < ofGetWindowWidth() && turret->boundary.y < ofGetWindowHeight() && turret->boundary.x > 0 && turret->boundary.y > 0)
			turret->linearVelocity += turret->heading * 25;
		else if (turret->boundary.y > ofGetWindowHeight())
			turret->setPosition(glm::vec3(turret->boundary.x, turret->boundary.y - 55, 1));
		else if (turret->boundary.y < 0)
			turret->setPosition(glm::vec3(turret->boundary.x, turret->boundary.y + 55, 1));
		else if (turret->boundary.x > ofGetWindowWidth())
			turret->setPosition(glm::vec3(turret->boundary.x - 55, turret->boundary.y, 1));
		else if (turret->boundary.x < 0)
			turret->setPosition(glm::vec3(turret->boundary.x + 55, turret->boundary.y, 1));
		break;
	//Rotate turret right
	case 'd':
	case OF_KEY_RIGHT:
		turret->angularVelocity += 15;
		break;
	//Rotate turret left
	case 'a':
	case OF_KEY_LEFT:
		turret->angularVelocity -= 15;
		break;
	//Shoot turret sprite missile
	case ' ':
		//If game started shoot sprite missile
		if (turret->started == true) {
			turret->shoot = true;
			turret->shootSound.play();
		}
		//Start the game and emitters
		else if (turret->started == false) {
			turret->start();
		}
	}
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	//Disable sprite missile shooting
	case ' ':
		turret->shoot = false;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

