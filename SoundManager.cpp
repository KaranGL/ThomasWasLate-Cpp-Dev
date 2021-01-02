#include "SoundManager.h"
#include <SFML/Audio.hpp>

using namespace sf;

SoundManager::SoundManager() {
	//loading sound into buffers
	mFireBuffer.loadFromFile("sound/fire1.wav");
	mFallInFireBuffer.loadFromFile("sound/fallinfire.wav");
	mFallInWaterBuffer.loadFromFile("sound/fallinwater.wav");
	mJumpBuffer.loadFromFile("sound/jump.wav");
	mReachGoalBuffer.loadFromFile("sound/reachgoal.wav");

	//connecting the sound with the buffers
	mFire1Sound.setBuffer(mFireBuffer);
	mFire2Sound.setBuffer(mFireBuffer);
	mFire3Sound.setBuffer(mFireBuffer);
	mFallInFireSound.setBuffer(mFallInFireBuffer);
	mFallInWaterSound.setBuffer(mFallInWaterBuffer);
	mJumpSound.setBuffer(mJumpBuffer);
	mReachGoalSound.setBuffer(mReachGoalBuffer);

	//when player is 50 pixel units away, sound is full volume
	float minDistance = 150;

	//sound reduces steadily as the player moves furthur away
	float attenuation = 15;

	//set all the attenuation levels
	mFire1Sound.setAttenuation(attenuation);
	mFire2Sound.setAttenuation(attenuation);
	mFire3Sound.setAttenuation(attenuation);
	
	//set all the min. distance levels
	mFire1Sound.setMinDistance(minDistance);
	mFire2Sound.setMinDistance(minDistance);
	mFire3Sound.setMinDistance(minDistance);

	//loop all the fire sounds when they are played
	mFire1Sound.setLoop(true);
	mFire2Sound.setLoop(true);
	mFire3Sound.setLoop(true);
}

void SoundManager::playFire(Vector2f emitterLocation, Vector2f listenerLocation) {
	//Where is the listener?
	Listener::setPosition(listenerLocation.x, listenerLocation.y, 0.f);

	switch (mNextSound) {
	case 1:
		//locate or move the source of the sound
		mFire1Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);

		if (mFire1Sound.getStatus() == Sound::Status::Stopped) {
			//play the sound if its not already playing
			mFire1Sound.play();
		}
		break;
	case 2:
		mFire2Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);

		if (mFire2Sound.getStatus() == Sound::Status::Stopped) {
			mFire2Sound.play();
		}
		break;
	case 3:
		mFire3Sound.setPosition(emitterLocation.x, emitterLocation.y, 0.0f);

		if (mFire3Sound.getStatus() == Sound::Status::Stopped) {
			mFire3Sound.play();
		}
		break;
	}

	//Increment to the next fire sound
	mNextSound++;

	//go back to 1 when the third sound has been started
	if (mNextSound > 3) {
		mNextSound = 1;
	}
}

void SoundManager::playFallInFire() {
	mFallInFireSound.setRelativeToListener(true);
	mFallInFireSound.play();
}

void SoundManager::playFallInWater() {
	mFallInWaterSound.setRelativeToListener(true);
	mFallInWaterSound.play();
}

void SoundManager::playJump() {
	mJumpSound.setRelativeToListener(true);
	mJumpSound.play();
}

void SoundManager::playReachGoal() {
	mReachGoalSound.setRelativeToListener(true);
	mReachGoalSound.play();
}