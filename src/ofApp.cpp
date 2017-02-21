#include "ofApp.h"

void ofApp::exit()
{
	soundManager.exit();
}

void ofApp::setup()
{
  	soundManager.setup(this);
}

void ofApp::update()
{
	soundManager.setTimecode(ofGetElapsedTimeMillis() - record_time);
	soundManager.update();
}

void ofApp::draw()
{
	soundManager.draw();

	if (soundManager.isRecording())
	{
		ofSetColor(255.0f, 0.0f, 0.0f);
		ofCircle(ofGetWidth() - 50.0f, 20.0f, 20.0f);
	}

	if (ofGetElapsedTimeMillis() - record_time > RECORD_DURATION)
	{
		soundManager.setRecording(false);
	}
}

void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key)
{
	switch (key)
	{
		case 'r': 
			record_time = ofGetElapsedTimeMillis();
			soundManager.record();
			break;

		case '1': 
		case '2': 
		case '3': 
		case '4': 
		case '5': 
		case '6': 
		case '7': 
		case '8': 
		case '9': 
			soundManager.setAlgorithm(key);
			break;
	}
}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
