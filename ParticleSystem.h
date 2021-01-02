#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.h"

using namespace sf;
using namespace std;

class ParticleSystem : public Drawable {
private:
	vector<Particle> mParticles;
	VertexArray mVertices;
	float mDuration;
	bool mIsRunning = false;

public:
	virtual void draw(RenderTarget& target, RenderStates states) const;
	void init(int count);
	void emitParticles(Vector2f position);
	void update(float elapsed);
	bool running();
};