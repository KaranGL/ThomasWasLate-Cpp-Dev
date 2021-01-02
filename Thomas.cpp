#include "Thomas.h"
#include "TextureHolder.h"

Thomas::Thomas() {
	mSprite = Sprite(TextureHolder::getTexture("graphics/thomas.png"));

	mJumpDuration = 0.45;
}

//A virtual function
bool Thomas::handleInput() {
	mJustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		//Start a jump if not already jumping but only if standing on a block (not falling)
		if (!mIsJumping && !mIsFalling) {
			mIsJumping = true;
			mTimeThisJump = 0;
			mJustJumped = true;
		}
	}
	else {
		mIsJumping = false;
		mIsFalling = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		mLeftPressed = true;
	}
	else {
		mLeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		mRightPressed = true;
	}
	else {
		mRightPressed = false;
	}

	return mJustJumped;
}