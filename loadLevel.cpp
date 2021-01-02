#include "Engine.h"

void Engine::loadLevel() {
	mPlaying = false;

	//delete the previous allocated memory
	for (int i = 0; i < mLM.getLevelSize().y; ++i) {
		delete[] mArrayLevel[i];
	}

	delete[] mArrayLevel;

	//load the next 2D array with the map for the level and repopulate the vertex array
	mArrayLevel = mLM.nextLevel(mVALevel);

	//prepare the sound emitters
	populateEmitters(mFireEmitters, mArrayLevel);

	//new time limit
	mTimeRemaining = mLM.getTimeLimit();

	//spawn both Thomas and Bob
	mThomas.spawn(mLM.getStartPosition(), GRAVITY);
	mBob.spawn(mLM.getStartPosition(), GRAVITY);

	//this code will not run again
	mNewlevel = false;
}