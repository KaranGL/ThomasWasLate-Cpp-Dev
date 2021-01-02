#include "Engine.h"

bool Engine::detectCollision(Player& character) {
	bool reachedGoal = false;

	//make a rect for all parts of the player
	FloatRect detectZone = character.getPosition();

	//Make the floatRect to test each block
	FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	//build a zone around thomas to detect collision
	int startx = (int)(detectZone.left / TILE_SIZE) - 1;

	int starty = (int)(detectZone.top / TILE_SIZE) - 1;
	
	int endx = (int)(detectZone.left / TILE_SIZE) + 2;

	//Thomas is tall, so we have to  check a few tiles vertically
	int endy = (int)(detectZone.top / TILE_SIZE) + 3;

	//Don't check postion lower than zero or higher than the end of array
	if (startx < 0) startx = 0;
	if (starty < 0) starty = 0;
	if (endx >= mLM.getLevelSize().x)endx = mLM.getLevelSize().x;
	if (endy >= mLM.getLevelSize().y)endy = mLM.getLevelSize().y;

	//has the character fallen out of the map?
	FloatRect level(0, 0, mLM.getLevelSize().x * TILE_SIZE, mLM.getLevelSize().y * TILE_SIZE);

	if (!character.getPosition().intersects(level)) {
		//respawn the character
		character.spawn(mLM.getStartPosition(), GRAVITY);
	}

	for (int i = startx; i < endx; i++) {
		for (int j = starty; j < endy; j++) {
			//initialize the starting position of the current block
			block.left = i * TILE_SIZE;
			block.top = j * TILE_SIZE;

			//has the character burnt or drowned?
			//use head as this allows him to sink
			if (mArrayLevel[j][i] == 2 || mArrayLevel[j][i] == 3) {
				if (character.getHead().intersects(block)) {
					character.spawn(mLM.getStartPosition(), GRAVITY);

					//sound to be played
					if (mArrayLevel[j][i] == 2) {	//FIRE TILE
						mSM.playFallInFire();
					}
					else {	//WATER TILE
						mSM.playFallInWater();
					}
				}
			}

			//is the character colliding with a normal block?
			if (mArrayLevel[j][i] == 1) {
				if (character.getRight().intersects(block)) {
					character.stopRight(block.left);
				}
				else if (character.getLeft().intersects(block)) {
					character.stopLeft(block.left);
				}

				if (character.getFeet().intersects(block)) {
					character.stopFalling(block.top);
				}
				else if (character.getHead().intersects(block)) {
					character.stopJump();
				}
			}

			
			//has the character's feet touched water or fire tile -- particle effect
			if (!mPS.running()) {
				if (mArrayLevel[j][i] == 2 || mArrayLevel[j][i] == 3) {
					if (character.getFeet().intersects(block)) {
						//start the particle effect
						mPS.emitParticles(character.getCenter());
					}
				}
			}

			//has character reached the goal?
			if (mArrayLevel[j][i] == 4) {
				reachedGoal = true;
			}
		}
	}

	//return whether or not a new level might be required
	return reachedGoal;
}