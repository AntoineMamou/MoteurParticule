#include "vector.h"

vect::vect() {
}

vect::vect(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float vect::getNorm() {
	return std::sqrtf(x * x + y * y + z * z);
}

// Fonction de multiplication d'un vecteur 3D avec un scalaire - Surcharge operator "*"
// input : un scalaire
// output : retourne le vecteur multiplié par le scalaire
vect vect::operator*(float constante) {
	return vect(x * constante, y * constante, z * constante);
}

// Fonction d'ajout de 2 vecteur 3D - Surcharge operator "+"
// input : un vecteur 3d
// output : retourne l'addition des 2 vecteurs
vect vect::operator+(vect & others) {
	return vect(x + others.x, y + others.y, z + others.z);
}

void vect::operator+=(vect & other) {
	x += other.x;
	y += other.y;
	z += other.z;
}

vect vect::operator-(vect & others) {
	vect returnValue;
	return vect(x - others.x, y - others.y, z - others.z);
	return returnValue;
}

float vect::ProduitScalaire(vect & others) {
	return this->x * others.x + this->y * others.y + this->z * others.z;
}

vect vect::ProduitVectoriel(vect & others) {
	vect value;
	value.x = this->y * others.z - this->z * others.y;
	value.y = this->z * others.x - this->x * others.z;
	value.z = this->x * others.y - this->y * others.x;
	return value;
}
