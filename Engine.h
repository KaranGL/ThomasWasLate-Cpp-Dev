#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Thomas.h"
#include "Bob.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "HUD.h"
#include "ParticleSystem.h"

using namespace sf;

class Engine {
private:
	TextureHolder holder;

	//create a particle system
	ParticleSystem mPS;

	//Thomas and bob instances
	Thomas mThomas;
	Bob mBob;

	LevelManager mLM;

	SoundManager mSM;

	HUD mHud;
	int mFrameSinceLastHUDUpdate = 0;
	int mTargetFramesPerHUDUpdate = 1000;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUADS = 4;
		
	//the force pushing the Thomas and Bob down
	const int GRAVITY = 300;

	RenderWindow mWindow;

	//The main views
	View mMainView, mLeftView, mRightView;

	//Three views for the background
	View mBGMainView, mBGLeftView, mBGRightView;

	View mHUDView;

	Sprite mBackgroundSprite;
	Texture mBackgroundTexture;

	//Is the game currently playing?
	bool mPlaying = false;

	//Is character 1 or 2 the current focus?
	bool mCharacter1 = true;

	//Start in fullScreen mode
	bool mSPLITScreen = false;

	//Time remaining in the current level
	float mTimeRemaining;
	Time mGameTOTALTime;

	//new/first level?
	bool mNewlevel = true;

	//The vertex array for the level design
	VertexArray mVALevel;

	//2D array with the map for the level
	int** mArrayLevel = NULL;

	//texture for the background and the level size
	Texture mTextureTiles;

	void input();
	void update(float timeAsSeconds);
	void draw();

	//loading a new level
	void loadLevel();

	bool detectCollision(Player& character);
		
	//make a vector of the best places to emit sounds from
	void populateEmitters(vector <Vector2f>& vSoundEmitters, int**arrayLevel);

	//a vector of vector2f for the fire emitter locations
	vector <Vector2f> mFireEmitters;
public:
	//constructor
	Engine();

	void run();
};