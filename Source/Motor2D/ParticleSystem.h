#pragma once
#include "p2Point.h"
#include "Particle.h"

class ParticleSystem
{
public:
	ParticleSystem(PARTICLE_TYPES type, p2Point<float>, int index, float timer);
	~ParticleSystem();

	void loadSystem(); //maybe we should load each effect properties from an xml
	bool activateSystem(int index);
	void Update(float dt);
	void deactivateAllParticles();
	void changePosition(fPoint location);
	void shootCannonBall(fPoint pos1, fPoint pos2);

	float timer;
	float countDown;
	bool timeActive;
	bool toDelete;

	//timer between activations
	int awakeningCounter;
	bool allParticlesAwake;

	ParticleProps systemProps;

private:

	PARTICLE_TYPES systemType;
	Particle* referencesArray[50];
	int numberOfParticles;

};