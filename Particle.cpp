#include "Particle.h"

Particle::Particle(Vector2f direction) {
	//determine the direction
	mVelocity.x = direction.x;
	mVelocity.y = direction.y;
}

void Particle::update(float dtAsSeconds) {
	//Move the particle
	mPosition += mVelocity * dtAsSeconds;
}

void Particle::setPosition(Vector2f position) {
	mPosition = position;
}

Vector2f Particle::getPosition() {
	return mPosition;
}