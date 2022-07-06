#pragma once

#include "Sprite.h"

//Sprite system class
class SpriteSystem {
public:
	//Add sprite function
	vector<Sprite> sprites;
	void add(Sprite s) {
		sprites.push_back(s);
	}
	//Delete sprite function
	void remove(int i) {
		sprites.erase(sprites.begin() + i);
	}
	//Sprite system update function
	void update() {
		if (sprites.size() == 0) return;
		//Delete sprites that are passed lifespan
		vector<Sprite>::iterator s = sprites.begin();
		vector<Sprite>::iterator tmp;
		while (s != sprites.end()) {
			if (s->lifespan != -1 && s->age() > s->lifespan) {
				tmp = sprites.erase(s);
				s = tmp;
			}
			else s++;
		}
		//Update sprites position
		for (int i = 0; i < sprites.size(); i++) {
			sprites[i].pos += sprites[i].velocity / ofGetFrameRate();
			//Update sprites hitbox
			sprites[i].hitBoxSprite.x = sprites[i].pos.x;
			sprites[i].hitBoxSprite.y = sprites[i].pos.y;
		}
	}
	//Draw sprite system function
	void draw() {
		for (int i = 0; i < sprites.size(); i++) {
			sprites[i].draw();
		}
	}
};