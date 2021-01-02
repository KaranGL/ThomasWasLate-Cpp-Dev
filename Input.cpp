#include "Engine.h"

void Engine::input() {
	Event event;
	
	while (mWindow.pollEvent(event)) {
		if (event.type==Event::KeyPressed) {
			//handle quitting
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				mWindow.close();
			}

			//handle starting the game
			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				mPlaying = true;
			}

			//Switch between Thomas and Bob
			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				mCharacter1 = !mCharacter1;
			}

			//Switch between split screen and full screen
			if (Keyboard::isKeyPressed(Keyboard::E)) {
				mSPLITScreen = !mSPLITScreen;
			}
		}
	}

	//handle input for Thomas
	if (mThomas.handleInput()) {
		//Jump Sound
		mSM.playJump();
	}

	//handle the input for Bob
	if (mBob.handleInput()) {
		//Jump Sound
		mSM.playJump();
	}
}