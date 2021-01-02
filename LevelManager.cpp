#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "LevelManager.h"
#include "TextureHolder.h"
#include "sstream"
#include "fstream"

using namespace sf;
using namespace std;

int** LevelManager::nextLevel(VertexArray& rVaLevel) {
	mLevelSize.x = 0;
	mLevelSize.y = 0;

	//get the next level
	mCurrentLevel++;
	if (mCurrentLevel>NUM_LEVELS) {
		mCurrentLevel = 1;
		mTimeModifier -= .1f;
	}

	//Load the appropriate level from the text file
	string levelToLoad;
	switch (mCurrentLevel) {
	case 1:
		levelToLoad = "levels/level1.txt";
		mStartPosition.x = 100;
		mStartPosition.y = 100;
		mBaseTimeLimit = 30.f;
		break;
	case 2:
		levelToLoad = "levels/level2.txt";
		mStartPosition.x = 100;
		mStartPosition.y = 3600;
		mBaseTimeLimit = 60.f;
		break;
	case 3:
		levelToLoad = "levels/level3.txt";
		mStartPosition.x = 1250;
		mStartPosition.y = 0;
		mBaseTimeLimit = 30.f;
		break;
	case 4:
		levelToLoad = "levels/level4.txt";
		mStartPosition.x = 50;
		mStartPosition.y = 200;
		mBaseTimeLimit = 50.f;
		break;
	case 5:
		levelToLoad = "levels/level5.txt";
		mStartPosition.x = 250;
		mStartPosition.y = 700;
		mBaseTimeLimit = 80.f;
		break;
	}

	ifstream inputFile(levelToLoad);
	string s;

	//count the number of rows in the file
	while (getline(inputFile, s)) {
		++mLevelSize.y;
	}

	//store the length of the rows
	mLevelSize.x = s.length();

	//go back to the start of the file
	inputFile.clear(); //clears the content of the file
	inputFile.seekg(0, ios::beg); //resets the string to the first character of the file

	//prepare the 2D array to hold the int values from the file
	int** arrayLevel = new int* [mLevelSize.y];
	for (int i = 0; i < mLevelSize.y; ++i) {
		//add a new array into each array element
		arrayLevel[i] = new int[mLevelSize.x];
	}

	//loop through the file and store all the values in the 2D array
	string row;
	int j = 0;

	while (inputFile >> row) {
		for (int i = 0; i < row.length(); i++ ) {
			const char val = row[i];
			arrayLevel[j][i] = atoi(&val);
		}

		j++;
	}

	//close the file
	inputFile.close();

	//What type of primitive are we using?
	rVaLevel.setPrimitiveType(Quads);

	//set the size of vertex array
	rVaLevel.resize(mLevelSize.x * mLevelSize.y * VERTZ_IN_QUAD);

	//start at the beginning of the vertex array
	int currentVertex = 0;

	for (int i = 0; i < mLevelSize.x; i++) {
		for (int j = 0; j < mLevelSize.y; j++) {
			//position each vertex in the current quad
			rVaLevel[currentVertex + 0].position = Vector2f(i * TILE_SIZE, j * TILE_SIZE);
			rVaLevel[currentVertex + 1].position = Vector2f((i * TILE_SIZE) + TILE_SIZE, j * TILE_SIZE);
			rVaLevel[currentVertex + 2].position = Vector2f((i * TILE_SIZE) + TILE_SIZE, (j * TILE_SIZE) + TILE_SIZE);
			rVaLevel[currentVertex + 3].position = Vector2f(i * TILE_SIZE, (j * TILE_SIZE) + TILE_SIZE);

			//Tile to be used from the sprite sheet
			int verticalOffset = arrayLevel[j][i] * TILE_SIZE;

			rVaLevel[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
			rVaLevel[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
			rVaLevel[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			rVaLevel[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			//position ready for the next four vertices
			currentVertex += VERTZ_IN_QUAD;
		}
	}
	return arrayLevel;
}

Vector2i LevelManager::getLevelSize() {
	return mLevelSize;
}

int LevelManager::getCurrentLevel() {
	return mCurrentLevel;
}

float LevelManager::getTimeLimit() {
	return mBaseTimeLimit * mTimeModifier;
}

Vector2f LevelManager::getStartPosition() {
	return mStartPosition;
}