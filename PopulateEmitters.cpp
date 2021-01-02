#include "Engine.h"

using namespace sf;
using namespace std;

void Engine::populateEmitters(vector <Vector2f>& vSoundEmitters, int** arrayLevel) {
	//make sure the vector is empty
	vSoundEmitters.empty();

	//Keep track of the previous emitter so that we don't make too many
	FloatRect previousEmitter;

	//search for fire in the level
	for (int x = 0; x < (int)mLM.getLevelSize().x; x++) {
		for (int y = 0; y < (int)mLM.getLevelSize().y; y++) {
			if (arrayLevel[y][x] == 2) {	// fire is present
				//skip over any fire tiles that are too near previous emitter
				if (!FloatRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE).intersects(previousEmitter)) {
					//add the coordiantes of this water block
					vSoundEmitters.push_back(
						Vector2f(x * TILE_SIZE, y * TILE_SIZE));

					//make a rectangle 6 blocks x 6 blocks, so we don't make any more emitters too close to this one
					previousEmitter.left = x * TILE_SIZE;
					previousEmitter.top = y * TILE_SIZE;
					previousEmitter.width = TILE_SIZE * 6;
					previousEmitter.height = TILE_SIZE * 6;
				}

			}

		}
	}
	return;
}