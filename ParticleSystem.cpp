#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

using namespace sf;
using namespace std;

void ParticleSystem::init(int numParticles) {
	mVertices.setPrimitiveType(Points);
	mVertices.resize(numParticles);

	//create the particle
	for (int i = 0; i < numParticles; i++) {
		srand(time(0) + i);
		float angle = (rand() % 360) * 3.14f / 180.f;
		float speed = (rand() % 600) + 600.f;
		
		Vector2f direction = Vector2f(cos(angle) * speed, sin(angle) * speed);

		mParticles.push_back(Particle(direction));
	}
}

void ParticleSystem::update(float dt) {
	mDuration -= dt;
	vector<Particle>::iterator i;
	int currentVertex = 0;

	for (i = mParticles.begin(); i != mParticles.end(); i++) {
		//move the particles
		(*i).update(dt);
		//update the vertex array
		mVertices[currentVertex].position = (*i).getPosition();
		//move to the next vertex
		currentVertex++;
	}

	if (mDuration <= 0) {
		mIsRunning = false;
	}
}

void ParticleSystem::emitParticles(Vector2f startPostion) {
	mIsRunning = true;
	mDuration = 2;

	vector<Particle>::iterator i;
	int currentVertex = 0;

	for (i = mParticles.begin(); i != mParticles.end(); i++) {
		mVertices[currentVertex].color = Color::Yellow;
		(*i).setPosition(startPostion);
		currentVertex++;
	}
}

void ParticleSystem::draw(RenderTarget& target, RenderStates states) const {
	target.draw(mVertices, states);
}

bool ParticleSystem::running() {
	return mIsRunning;
}