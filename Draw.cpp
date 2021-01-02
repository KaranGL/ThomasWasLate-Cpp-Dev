#include "Engine.h"

void Engine::draw() {
	//rub out the last frame
	mWindow.clear(Color::White);

	if (!mSPLITScreen) {
		//Switch to background view
		mWindow.setView(mBGMainView);
		
		//draw the background with shader
		mWindow.draw(mBackgroundSprite);

		//Switch to mMainview
		mWindow.setView(mMainView);

		//draw a level
		mWindow.draw(mVALevel, &mTextureTiles);

		//Draw Thomas
		mWindow.draw(mThomas.getSprite());
		
		//draw Bob
		mWindow.draw(mBob.getSprite());
		
		//draw the particle system
		if(mPS.running()){
			mWindow.draw(mPS);
		}
	}
	else {
		//Thomas's side of the screen
		mWindow.setView(mBGLeftView);
		//draw the background with shader
		mWindow.draw(mBackgroundSprite);
		mWindow.setView(mLeftView);

		mWindow.draw(mVALevel, &mTextureTiles);

		//draw Bob
		mWindow.draw(mBob.getSprite());
		//draw Thomas
		mWindow.draw(mThomas.getSprite());
		
		//draw the particle system
		if (mPS.running()) {
			mWindow.draw(mPS);
		}

		//Bob's side of the screen
		mWindow.setView(mBGRightView);
		//draw the background with shader
		mWindow.draw(mBackgroundSprite);
		mWindow.setView(mRightView);

		mWindow.draw(mVALevel, &mTextureTiles);

		//draw Thomas
		mWindow.draw(mThomas.getSprite());

		//draw Bob
		mWindow.draw(mBob.getSprite());

		//draw the particle system
		if (mPS.running()) {
			mWindow.draw(mPS);
		}
	}

	//draw the HUD
	mWindow.setView(mHUDView);
	mWindow.draw(mHud.getLevel());
	mWindow.draw(mHud.getTime());
	if (!mPlaying) {
		mWindow.draw(mHud.getMessage());
	}

	mWindow.display();
}