#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class HUD {
private:
	Font mFont;
	Text mStartText;
	Text mTimeText;
	Text mLevelText;

public:
	HUD();

	Text getMessage();
	Text getLevel();
	Text getTime();

	void setLevel(String text);
	void setTime(String text);
};