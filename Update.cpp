#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

void Engine::update(float timeAsSeconds) {
	if (mNewlevel) {
		//load a level
		loadLevel();
	}

	if (mPlaying) {
		//Update Thomas
		mThomas.update(timeAsSeconds);
		//Update Bob
		mBob.update(timeAsSeconds);

		//detect collision and check if the player has reached the goal
		if (detectCollision(mThomas) && detectCollision(mBob)) {
			mNewlevel = true;
			
			mSM.playReachGoal();
		}
		else {
			detectCollision(mBob);
		}

		//bob and thomas's ability to jump on each others heads
		if (mBob.getFeet().intersects(mThomas.getHead())) {
			mBob.stopFalling(mThomas.getHead().top);
		}
		else if (mThomas.getFeet().intersects(mBob.getHead())) {
			mThomas.stopFalling(mBob.getHead().top);
		}

		//time remaining
		mTimeRemaining -= timeAsSeconds;
		
		//Has the player run out of time?
		if (mTimeRemaining <= 0) {
			mNewlevel = true;
		}	
	}

	//check if the fire sound needs to be played
	vector <Vector2f>::iterator it;

	//iterate through the vector of Vector2f objects
	for (it = mFireEmitters.begin(); it != mFireEmitters.end(); it++) {
		//where is this emitter
		float posX = (*it).x;
		float posY = (*it).y;

		//is the emitter near the player? make a 500 pixel rectangle around the emitter
		FloatRect localRect(posX - 250, posY - 250, 500, 500);

		//is the player inside  localRect?
		if (mThomas.getPosition().intersects(localRect)) {
			mSM.playFire(Vector2f(posX, posY), mThomas.getCenter());
		}
	}

	//Set the appropriate view around the appropriate character
	if (mSPLITScreen) {
		mLeftView.setCenter(mThomas.getCenter());
		mRightView.setCenter(mBob.getCenter());
	}
	else {
		//centre full screen around appropriate character
		if (mCharacter1) {
			mMainView.setCenter(mThomas.getCenter());
		}
		else {
			mMainView.setCenter(mBob.getCenter());
		}
	}

	//Increment the number of frames since the last HUD update
	mFrameSinceLastHUDUpdate++;

	//update the hud every mTargetFramesPerHUDUpdate frames
	if (mFrameSinceLastHUDUpdate > mTargetFramesPerHUDUpdate) {
		//update the game HUD text
		stringstream ssTime;
		stringstream ssLevel;

		//update the time text
		ssTime << (int)mTimeRemaining;
		mHud.setTime(ssTime.str());

		//update the level text
		ssLevel << "Level: " << mLM.getCurrentLevel();
		mHud.setLevel(ssLevel.str());

		mFrameSinceLastHUDUpdate = 0;
	}

	//update the particles
	if (mPS.running()) {
		mPS.update(timeAsSeconds);
	}
}