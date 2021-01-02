#include "HUD.h"

HUD::HUD() {
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	//load the font
	mFont.loadFromFile("fonts/Roboto-Light.ttf");

	//Paused
	mStartText.setFont(mFont);
	mStartText.setCharacterSize(100);
	mStartText.setFillColor(Color::White);
	mStartText.setString("Press Enter to play");

	//position the text
	FloatRect textRect = mStartText.getLocalBounds();

	mStartText.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);

	mStartText.setPosition(resolution.x / 2.f, resolution.y / 2.f);

	//Time
	mTimeText.setFont(mFont);
	mTimeText.setCharacterSize(75);
	mTimeText.setFillColor(Color::White);
	mTimeText.setPosition(resolution.x - 150, 0);
	mTimeText.setString("------");
	
	//Level
	mLevelText.setFont(mFont);
	mLevelText.setCharacterSize(75);
	mLevelText.setFillColor(Color::White);
	mLevelText.setPosition(25, 0);
	mLevelText.setString("1");
}

Text HUD::getMessage() {
	return mStartText;
}

Text HUD::getLevel() {
	return mLevelText;
}

Text HUD::getTime() {
	return mTimeText;
}

void HUD::setLevel(String text) {
	mLevelText.setString(text);
}

void HUD::setTime(String text) {
	mTimeText.setString(text);
}