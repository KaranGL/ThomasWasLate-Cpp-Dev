#include "Bob.h"
#include "TextureHolder.h"

Bob::Bob() {
	mSprite = Sprite(TextureHolder::getTexture("graphics/bob.png"));

	mJumpDuration = 0.25;
}

bool Bob::handleInput() {
	mJustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::Up)) {

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

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		mLeftPressed = true;
	}
	else {
		mLeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		mRightPressed = true;;
	}
	else {
		mRightPressed = false;
	}

	return mJustJumped;
}