#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->noise_step = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 50 < 30) {

		this->noise_step += ofMap(ofGetFrameNum() % 50, 0, 30, 0.02, 0.0001);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto numberOfActor = 300;
	auto len = 150;
	ofColor color;

	ofSeedRandom(39);
	for (int i = 0; i < numberOfActor; i++) {

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		color.setHsb(ofRandom(255), 255, 255, 32);
		
		for (int k = 0; k < len; k++) {

			auto location = glm::vec2(
				ofMap(ofNoise(noise_seed.x, k * 0.0005 + this->noise_step), 0, 1, -500, 500),
				ofMap(ofNoise(noise_seed.y, k * 0.0005 + this->noise_step), 0, 1, -500, 500));

			if (glm::length(location) < 100) {

				location = glm::normalize(location) * 100;
			}

			if (glm::length(location) > 300) {

				location = glm::normalize(location) * 300;
			}

			ofSetColor(color);
			ofDrawCircle(location, 3);

			ofSetColor(255);
			ofDrawCircle(location, 1);
		}
	}

	/*
	int start = 300;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}