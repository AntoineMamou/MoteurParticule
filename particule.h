#pragma once
#include "baseObject.h"
#include "ofMain.h"
#include "vector.h"

class particule : baseObject {
private:
	vect position, vitesse, acceleration;
	float damping, gravity, masse;
	std::vector<vect> trace;

public:
	particule();
	particule(vect pos, vect vit);
	particule(vect pos, vect vit, vect acc);
	vect getPosition();
	vect getVitesse();
	vect getAccel();

	void setMasse(float m);
	void setGravity(float g);
	void setDamping(float f);

	float getMasse();
	float getGravity();
	float getDamping();

	std::vector<vect> getTraceArray();
	void addTracePosition(vect pos);
	void drawTrace();
	void drawTrace(ofColor color);

	void computeForce();
	void setPosition(vect pos);
	void updatePosition(float time);
	void EulerIntegration(float time);
	void VerletIntegration(float time);
	void draw();
};
