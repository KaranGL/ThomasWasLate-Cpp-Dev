#pragma once
#include <SFML/Audio.hpp>

using namespace sf;

class SoundManager {
private:
	//sound buffers
	SoundBuffer mFireBuffer;
	SoundBuffer mFallInFireBuffer;
	SoundBuffer mFallInWaterBuffer;
	SoundBuffer mJumpBuffer;
	SoundBuffer mReachGoalBuffer;

	//Sound
	Sound mFire1Sound;
	Sound mFire2Sound;
	Sound mFire3Sound;
	Sound mFallInFireSound;
	Sound mFallInWaterSound;
	Sound mJumpSound;
	Sound mReachGoalSound;

	//which sound to use next? Fire 1, 2 or 3?
	int mNextSound = 1;
public:
	SoundManager();

	void playFire(Vector2f emitterLocation, Vector2f listenerLocation);
	void playFallInFire();
	void playFallInWater();
	void playJump();
	void playReachGoal();
};