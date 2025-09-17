#include "particule.h"

particule::particule() {
}

particule::particule(vect pos, vect vit) {
	position = pos;
	vitesse = vit;
	gravity = 0.0f;
	masse = 0.0f;
	acceleration = { 0, 0, 0 };
	damping = 0.0f;
}

particule::particule(vect pos, vect vit, vect acc) {
	position = pos;
	vitesse = vit;
	damping = 0;
	masse = 0;
	gravity = 0;
	acceleration = acc;
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

void particule::computeForce() {
	//Calcul de la force de frottement
	acceleration = vitesse * (-damping / masse);
	//Ajout de la force de frotement (Positive car on est dans un repere retourne)
	acceleration.y += gravity;
}

void particule::EulerIntegration(float time) {
	vect deltaVitesse = acceleration * time;
	vitesse = vitesse + deltaVitesse;
	vect deplacement = vitesse * time;

	//On retourne la composante de vitesse verticale, car le repere de dessin est inverse
	// 0 --> haut de l'ecran
	deplacement.y *= (-1);

	//Nouvelle position = ancienne position + deplacement
	position = position + deplacement;
}

void particule::VerletIntegration(float time) {
	vect previous_pos = position;
	vect temp = acceleration * time * time;
	position = position * 2 - previous_pos + temp;
}

void particule::setMasse(float m) {
	masse = m;
}

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

std::vector<vect> particule::getTraceArray() {
	return trace;
}
void particule::addTracePosition(vect pos) {
	trace.push_back(pos);
}

void particule::drawTrace() {
	if (trace.size() >= 2) {
		for (int i = 1; i < trace.size(); i++) {
			ofDrawLine(glm::vec3(trace[i - 1].x, trace[i - 1].y, trace[i - 1].z), glm::vec3(trace[i].x, trace[i].y, trace[i].z));
		}
	}
}

void particule::drawTrace(ofColor color) {
	ofSetColor(color);
	drawTrace();
	ofSetColor(ofColor(255, 255, 255));
}
