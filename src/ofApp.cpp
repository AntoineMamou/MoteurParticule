#include "ofApp.h"
#include <numbers>

std::vector<particule> particuleArray;
float angle = 45;
float duration = 0;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0, 0);

	vect v1 = { 1, 0, 0 };
	vect v2 = { 0, 1, 0 };

	int a = v1.ProduitScalaire(v2);
	vect a1 = v1.ProduitVectoriel(v2);
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
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (auto & part : particuleArray) {
		part.drawTrace(ofColor(127, 0, 0));
		part.draw();
	}

	ofDrawBitmapStringHighlight("800 metres", 930, 600);
	ofDrawArrow(glm::vec3(100, 600, 0), glm::vec3(900, 600, 0), 2);

	duration += 1 / ofGetFrameRate();
	char msgTime[128];
	sprintf(msgTime, "Duree de la simulation : %.2f (s)", duration);
	ofDrawBitmapStringHighlight(msgTime, 100, 100);

	char msgAngle[128];
	sprintf(msgAngle, "Angle : %.f ", angle);
	ofDrawBitmapStringHighlight(msgAngle, 100, 120);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == 112) {
		particule p1({ ofRandom(ofGetWindowSize().x), ofRandom(ofGetWindowSize().y), 0 }, { ofRandom(100), ofRandom(100), 0 });
		p1.setDamping(0.01);
		p1.setMasse(12);
		p1.setGravity(-9.81);
		particuleArray.push_back(p1);
	}
	if (key == 'c') {
		float speed = 100; // vitesse initiale de 100m/s
		particule canon({ 100, 600, 0 }, { speed * std::cosf(angle / 360 * 2 * std::numbers::pi), speed * std::sinf(angle / 360 * 2 * std::numbers::pi), 0 }, { 0, 0, 0 });
		canon.setDamping(1.5);
		canon.setMasse(12);
		canon.setGravity(-9.81);
		particuleArray.push_back(canon);
	}
	// send a laser beam
	if (key == 'l') {
		float speed = 500;
		particule laser({ 100, 600, 0 }, { speed * std::cosf(angle / 360 * 2 * std::numbers::pi), speed * std::sinf(angle / 360 * 2 * std::numbers::pi), 0 }, { 0, 0, 0 });
		laser.setDamping(0.000);
		laser.setMasse(0.0001f);
		laser.setGravity(-9.81);
		particuleArray.push_back(laser);
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
