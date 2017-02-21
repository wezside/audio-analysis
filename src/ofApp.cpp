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
	soundManager.update();
}

void ofApp::draw()
{
	soundManager.draw();
}

void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key)
{
	switch (key)
	{
		case 'r': 
			soundManager.record();
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
