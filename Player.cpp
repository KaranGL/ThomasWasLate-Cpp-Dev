#include "Player.h"

void Player::spawn(Vector2f startPosition, float gravity) {
	//place the player at the starting position
	mPosition.x = startPosition.x;
	mPosition.y = startPosition.y;

	//initialize the gravity
	mGravity = gravity;

	//Move the sprite in to position
	mSprite.setPosition(mPosition);
}

void Player::update(float elapsedTime) {
	if (mRightPressed) {
		mPosition.x += mSpeed * elapsedTime;
	}
	
	if (mLeftPressed) {
		mPosition.x -= mSpeed * elapsedTime;
	}

	//handle jumping
	if (mIsJumping) {
		//update how long the jump has been going
		mTimeThisJump += elapsedTime;

		//is jump going upwards
		if (mTimeThisJump < mJumpDuration) {
			//move up at twice gravity
			mPosition.y -= mGravity * 2 * elapsedTime;
		}
		else {
			mIsJumping = false;
			mIsFalling = true;
		}
	}

	//Apply gravity
	if (mIsFalling) {
		mPosition.y += mGravity * elapsedTime;
	}

	//update the rect for all the body parts
	FloatRect r = getPosition();
	
	//Feet
	mFeet.left = r.left + 3;
	mFeet.top = r.top + r.height - 1;
	mFeet.width = r.width - 6;
	mFeet.height = 1;

	//head
	mHead.left = r.left;
	mHead.top = r.top + (r.height * .3);
	mHead.width = r.width;
	mHead.height = 1;

	//right
	mRight.left = r.left + r.width - 2;
	mRight.top = r.top + r.height * .35;
	mRight.width = 1;
	mRight.height = r.height * .3;

	//left
	mLeft.left = r.left;
	mLeft.top = r.top + r.height * .5;
	mLeft.width = 1;
	mLeft.height = r.height * .3;

	//Move the sprite into position
	mSprite.setPosition(mPosition);
}

FloatRect Player::getPosition() {
	return mSprite.getGlobalBounds();
}

Vector2f Player::getCenter() {
	return Vector2f(mPosition.x + mSprite.getGlobalBounds().width / 2, mPosition.y + mSprite.getGlobalBounds().height / 2);
}

FloatRect Player::getFeet() {
	return mFeet;
}

FloatRect Player::getHead() {
	return mHead;
}

FloatRect Player::getLeft() {
	return mLeft;
}

FloatRect Player::getRight() {
	return mRight;
}

Sprite Player::getSprite() {
	return mSprite;
}

void Player::stopFalling(float position) {
	mPosition.y = position - getPosition().height;
	mSprite.setPosition(mPosition);
	mIsFalling = false;
}

void Player::stopRight(float position) {
	mPosition.x = position - mSprite.getGlobalBounds().width;
	mSprite.setPosition(mPosition);
}

void Player::stopLeft(float position) {
	mPosition.x = position + mSprite.getGlobalBounds().width;
	mSprite.setPosition(mPosition);
}

void Player::stopJump() {
	// Stop a jump early 
	mIsJumping = false;
	mIsFalling = true;
}