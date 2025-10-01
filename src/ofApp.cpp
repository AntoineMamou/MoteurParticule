#include "ofApp.h"
#include <numbers>
#include "..//testVector.h";

std::vector<particule> particuleArray;
std::vector<particule> blobArray;
float angle = 30;
float duration = 0;
float speedBlob = 1000;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0, 0);

	TestVector::runTests();
}

//--------------------------------------------------------------
void ofApp::update() {
	for (auto & part : particuleArray) {
		if (part.getPosition().y <= 600) {
			float time = 1 / ofGetFrameRate();
			part.computeForce();
			part.EulerIntegration(time);
			part.addTracePosition(part.getPosition());
		}
	}

	for (auto & part : blobArray){
		float time = 1 / ofGetFrameRate();
		part.computeForce();
		part.EulerIntegration(time);

	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (auto & part : particuleArray) {
		part.drawTrace(ofColor(127, 0, 0));
		part.draw();
	}

	for (auto & part : blobArray) {
		part.draw();
	}


	ofDrawBitmapStringHighlight("800 metres", 930, 600);
	ofDrawArrow(glm::vec3(100, 600, 0), glm::vec3(900, 600, 0), 2);

	duration += 1 / ofGetFrameRate();
	char msgTime[128];
	sprintf(msgTime, "Durée de la simulation : %.2f (s)", duration);
	ofDrawBitmapStringHighlight(msgTime, 100, 100);

	char msgAngle[128];
	sprintf(msgAngle, "Angle : %.f °", angle);
	ofDrawBitmapStringHighlight(msgAngle, 100, 120);

	char cmd[256];
	sprintf(cmd, "Commandes :\n\nLancer boule de feu : 'f'\nLancer balle : 'b'\nTirer laser : 'l'\nLancer boule de canon : 'c'\n\nModifier l'angle de tir : flèche directionnelle up/dwn\n\nReset l'affichage : backspace");
	ofDrawBitmapStringHighlight(cmd, 600, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 112) {
		particule p1({ ofRandom(ofGetWindowSize().x), ofRandom(ofGetWindowSize().y), 0 }, { ofRandom(100), ofRandom(100), 0 });
		p1.setDamping(0.01);
		p1.setMasse(12);
		p1.setGravity(-9.81);
		particuleArray.push_back(p1);
	}
	if (key == 'c') {
		float speed = 150; // vitesse initiale de 150m/s
		particule canon({ 100, 550, 0 }, { speed * std::cosf(angle / 360 * 2 * std::numbers::pi), speed * std::sinf(angle / 360 * 2 * std::numbers::pi), 0 }, { 0, 0, 0 });
		canon.setDamping(0.03);
		canon.setMasse(12);
		canon.setGravity(-9.81);
		particuleArray.push_back(canon);
	}

	// send a laser beam
	if (key == 'l') {
		float speed = 5000;
		particule laser({ 100, 550, 0 }, { speed * std::cosf(angle / 360 * 2 * std::numbers::pi), speed * std::sinf(angle / 360 * 2 * std::numbers::pi), 0 }, { 0, 0, 0 });
		laser.setDamping(0.0f);
		laser.setMasse(0.0f);
		laser.setGravity(-9.81);
		particuleArray.push_back(laser);
	}

	if (key == 'f') {
		float speed = 50;
		particule fireball({ 100, 550, 0 }, { speed * std::cosf(angle / 360 * 2 * std::numbers::pi), speed * std::sinf(angle / 360 * 2 * std::numbers::pi), 0 }, { 0, 0, 0 });
		fireball.setDamping(0.0f);
		fireball.setMasse(0.0f);
		fireball.setGravity(0);
		particuleArray.push_back(fireball);
	}

	if (key == 'b') {
		float speed = 500;
		particule bullet({ 100, 550, 0 }, { speed * std::cosf(angle / 360 * 2 * std::numbers::pi), speed * std::sinf(angle / 360 * 2 * std::numbers::pi), 0 }, { 0, 0, 0 });
		bullet.setDamping(0.0001f);
		bullet.setMasse(0.01f);
		bullet.setGravity(-9.81f);
		particuleArray.push_back(bullet);
	}

	// Spawn Blob
	if (key == 'x') {
		particule blob({ 500, 500, 0 }, { 0, 0, 0 });
		blob.setDamping(0.0001f);
		blob.setMasse(0.01f);
		blob.setGravity(0);
		blobArray.push_back(blob);
	}

	if (key == 'w') {
		for (particule c : blobArray) {
			c.applySpeed({0, -speedBlob, 0});
		}
	}
	if (key == 's') {
		for (particule c : blobArray) {
			c.applySpeed({ 0, speedBlob, 0 });
		}
	}
	if (key == 'a') {
		for (particule c : blobArray) {
			c.applySpeed({ -speedBlob, 0, 0 });
		}
	}
	if (key == 'd') {
		for (particule c : blobArray) {
			c.applySpeed({ speedBlob, 0, 0 });
		}
	}

	if (key == 8) {
		particuleArray.clear();
	}
	// Arrow down
	if (key == 57359) {
		angle -= 1;
	}

	// Arrow up
	if (key == 57357) {
		angle += 1;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == 's') {
		for (particule c : blobArray) {
			c.applySpeed({ 0, -speedBlob, 0 });
		}
	}
	if (key == 'w') {
		for (particule c : blobArray) {
			c.applySpeed({ 0, speedBlob, 0 });
		}
	}
	if (key == 'd') {
		for (particule c : blobArray) {
			c.applySpeed({ -speedBlob, 0, 0 });
		}
	}
	if (key == 'a') {
		for (particule c : blobArray) {
			c.applySpeed({ speedBlob, 0, 0 });
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}
