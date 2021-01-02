#pragma once
#include "Player.h"

class Thomas : public Player {
	public:
		Thomas();

		//the overridden input handler for thomas
		bool virtual handleInput();
};