#include "Engine.h"

Engine::Engine() {
	//Get the screen resolution and create a render window
	Vector2f resolution;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	
	mWindow.create(VideoMode(resolution.x, resolution.y), "Thomas Was Late", Style::Fullscreen);

	//Initialize the full screen view
	mMainView.setSize(resolution);
	mHUDView.reset(FloatRect(0, 0, resolution.x, resolution.y));

	//Initialize the split screen view
	mLeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));

	mRightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

	mBGLeftView.setViewport(FloatRect(0.001f, 0.001f, 0.498f, 0.998f));
	
	mBGRightView.setViewport(FloatRect(0.5f, 0.001f, 0.499f, 0.998f));

	mBackgroundTexture = TextureHolder::getTexture("graphics/background.png");

	mBackgroundSprite.setTexture(mBackgroundTexture);

	//load the texture for the background vertex array
	mTextureTiles = TextureHolder::getTexture("graphics/tiles_sheet.png");

	//Initialize the particle system
	mPS.init(1000);
}

void Engine::run() {
	//Timing of the game
	Clock clock;

	while (mWindow.isOpen()) {
		Time time = clock.restart();
		//Update the total game time
		mGameTOTALTime += time;
		float timeAsSeconds = time.asSeconds();

		//call for each part of the game loop in turn
		input();
		update(timeAsSeconds);
		draw();
	}
}