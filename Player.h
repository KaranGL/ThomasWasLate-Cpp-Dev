#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
protected:
	Sprite mSprite;

	//Jump duration
	float mJumpDuration;

	//Jumping or falling?
	bool mIsJumping;
	bool mIsFalling;

	//player's movement direction
	bool mLeftPressed;
	bool mRightPressed;

	//Timing a jump
	float mTimeThisJump;

	//Has the player just initiated a jump
	bool mJustJumped = false;
private:
	//Gravity
	float mGravity;

	//player speed
	float mSpeed = 400;

	//player position
	Vector2f mPosition;

	//Where are the characters various body parts?
	FloatRect mFeet;
	FloatRect mHead;
	FloatRect mRight;
	FloatRect mLeft;

	Texture mTexture;
public:
	void spawn(Vector2f startPosition, float gravity);

	//pure virtual function			//This class is now abstract and cannot be instanciated
	bool virtual handleInput() = 0;

	//get player's position
	FloatRect getPosition();

	//A rectangle representing the position of different parts of the sprite
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();

	//Send a copy of the sprite to main
	Sprite getSprite();

	//Make the character stand firm
	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	//Center of the character
	Vector2f getCenter();

	void update(float elapsedTime);
};