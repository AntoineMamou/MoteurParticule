#include "particule.h"
#include <numbers>

particule::particule() {
}

particule::particule(vect pos, vect vit) {
	position = pos;
	vitesse = vit;
	gravity = 0.0f;
	masse = 0.0f;
	acceleration = { 0, 0, 0 };
	damping = 0.0f;
	trace.push_back(pos);
}

particule::particule(vect pos, vect vit, vect acc) {
	position = pos;
	vitesse = vit;
	damping = 0;
	masse = 0;
	gravity = 0;
	acceleration = acc;
	trace.push_back(pos);
}

vect particule::getPosition() { return position; }
void particule::setPosition(vect pos) { position = pos; }
vect particule::getAccel() { return acceleration; }

vect particule::getVitesse() { return vitesse; }

void particule::updatePosition(float time) {
	vect deplacement(vitesse * time);
	position = position + deplacement;
}

void particule::draw() {
	ofDrawCircle(glm::vec3(position.x, position.y, position.z), 5);
}

/// <summary>
/// Function that computes accelerations based on the forces applied to the particle
/// </summary>

void particule::computeForce() {
	if (masse != 0) {
		// Computing the friction force: friction_force = -f * v^2
		acceleration.x = std::abs(vitesse.getNorm()) * vitesse.x * -damping / masse;
		acceleration.y = std::abs(vitesse.getNorm()) * vitesse.y * -damping / masse;
	}
	// Adding the friction force (Positive since the reference frame is inverted)
	acceleration.y += gravity;
}

/// <summary>
///
/// </summary>
/// <param name="time"></param>
void particule::EulerIntegration(float time) {
	vect deltaVitesse = acceleration * time;
	vitesse = vitesse + deltaVitesse;
	vect deplacement = vitesse * time;

	/* ######## FOR DEBUG ########
	* 
	printf("acc (y) = %f\n", acceleration.y);
	printf("vit (y) = %f\n\n", vitesse.y);
	printf("deplacement (y) = %f\n\n", deplacement.y);

	printf("acc (x) = %f\n", acceleration.x);
	printf("vit (x) = %f\n", vitesse.x);
	printf("deplacement (x) = %f\n\n", deplacement.x);

	printf("angle : %f\n", std::atanf(vitesse.y / vitesse.x) * 180 / std::numbers::pi);

	printf("------------------------\n");
	*/

	// Invert the vertical velocity component, since the rendering coordinate system is inverted
	// 0 --> top of the screen
	deplacement.y *= (-1);

	// New position = previous position + movement
	position = position + deplacement;
}

/// <summary>
/// In development
/// </summary>
/// <param name="time"></param>
void particule::VerletIntegration(float time) {
	vect previous_pos = position;
	vect temp = acceleration * time * time;
	position = position * 2 - previous_pos + temp;
}

/// <summary>
/// Function to modify the mass of the particle
/// </summary>
///
/// <param name="m">masse de la particule</param>
void particule::setMasse(float m) {
	masse = m;
}

/// <summary>
/// Function to modify the gravity applied to the particle
/// </summary>
/// <param name="g"></param>
void particule::setGravity(float g) {
	gravity = g;
}

void particule::setDamping(float f) {
	damping = f;
}

float particule::getMasse() {
	return masse;
}

float particule::getGravity() {
	return gravity;
}

float particule::getDamping() {
	return damping;
}

/// <summary>
/// Function which return an array with all the positions all the previous positions of the particle
/// </summary>
/// <returns>
/// Vector<Vect> storing the past positions
/// </returns>
std::vector<vect> particule::getTraceArray() {
	return trace;
}
void particule::addTracePosition(vect pos) {
	trace.push_back(pos);
}

/// <summary>
/// Function that plots a line through all the past positions
/// </summary>
void particule::drawTrace() {
	if (trace.size() >= 2) {
		for (int i = 1; i < trace.size(); i++) {
			ofDrawLine(glm::vec3(trace[i - 1].x, trace[i - 1].y, trace[i - 1].z), glm::vec3(trace[i].x, trace[i].y, trace[i].z));
		}
	}
}

/// <summary>
/// Allows drawing the trail of an object by specifying the trail color
/// </summary>
/// <param name="color">
/// Trail color in the format: ofColor(R,G,B)
/// </param>
void particule::drawTrace(ofColor color) {
	ofSetColor(color);
	drawTrace();
	ofSetColor(ofColor(255, 255, 255));
}
