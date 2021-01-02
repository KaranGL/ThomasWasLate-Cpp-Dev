#pragma once
#include "Player.h"

class Bob : public Player {
public:
	Bob();

	//the overridden input handler for bob
	bool virtual handleInput();
};