#include "soundmanager.hpp"

void wezside::SoundManager::exit()
{
	ofSoundStreamStop();
	audioAnalyzer.exit();
}

void wezside::SoundManager::setup(ofBaseApp *app)
{
	int sampleRate = 44100;
	int bufferSize = 512;
	int outChannels = 0;
	int inChannels = 2;
	
	// soundStream.printDeviceList();
	soundStream.setDevice(soundStream.getDeviceList().at(12));

	// setup the sound stream
	soundStream.setup(app, outChannels, inChannels, sampleRate, bufferSize, 3);
	
	//setup ofxAudioAnalyzer with the SAME PARAMETERS
	audioAnalyzer.setup(sampleRate, bufferSize, inChannels);

	colors[0] = ofColor::aqua;
	colors[1] = ofColor::forestGreen;
	colors[2] = ofColor::lightPink;
	colors[3] = ofColor::lemonChiffon;
	colors[4] = ofColor::lavender;
}


void wezside::SoundManager::analyze(ofSoundBuffer &inBuffer)
{
	audioAnalyzer.analyze(inBuffer);
}

void wezside::SoundManager::update()
{
	smooth = ofClamp(ofGetMouseX() / (float)ofGetWidth(), 0.0, 1.0);
	
	//get the analysis values
	rms_l = audioAnalyzer.getValue(RMS, 0, smooth);
	rms_r = audioAnalyzer.getValue(RMS, 1, smooth);

	// Get Pitch Frequency
	pitch_freq = audioAnalyzer.getValue(PITCH_FREQ, 0, smooth, TRUE);
	pitch_freq = ofMap(pitch_freq, 0.0f, 1.0f, 0.0f, 1.0f);

	// Get High Frequency Content
	hfc = audioAnalyzer.getValue(HFC, 0, smooth);

	// Power/Energy
	power = audioAnalyzer.getValue(POWER, 0, smooth);

	if (recording)
	{
		switch (algorithm)
		{
			case '1':
				recording[recording_index][data_index] = (rms_l + rms_r) / 2.0f;
				break;
			case '2':
				recording[recording_index][data_index] = pitch_freq;
				break;
			case '3':
				recording[recording_index][data_index] = hfc;
				break;			
			case '4':
				recording[recording_index][data_index] = power;
				break;	
			case '5':
				break;	
		}
		data_index++;
		if (data_index >= RECORDING_SIZE) data_index = 0;
	}
}

void wezside::SoundManager::draw()
{
	int gap = 2;
	int spacing = 10;
	int y = ofGetHeight() * 0.5f;

	for (int i = 0; i < RECORDING_NUM; ++i)
	{
		for (int j = 0; j < RECORDING_SIZE; ++j)
		{
			ofSetColor(colors[recording_index]);
			ofDrawRectangle(j * spacing + gap, y, j * spacing, recording[i][j]);
		}
	}

	int xoffset = ofGetWidth() - 250;
	ofSetColor(ofColor::cyan);
	ofDrawRectangle(xoffset + 20.0, 82.0, rms_l * 170.0, 8.0);

	ofSetColor(ofColor::hotPink);
	ofDrawRectangle(xoffset + 20.0, 95.0, rms_r * 170.0, 8.0);
	
	//----------------
	
	ofSetColor(225);
	string infoString = "RMS Left: " + ofToString(rms_l, 3) +
						"\nRMS Right: " + ofToString(rms_r, 3) +
						"\nSmoothing (mouse): " + ofToString(smooth, 3) + 
						"\nL" + 
						"\nR";
	

	infoString += "\n\nPITCH FREQUENCY " + ofToString(pitch_freq, 3);
	infoString += "\n\nHIGH FREQUENCY CONTENT " + ofToString(hfc, 3);
	infoString += "\n\nENERGY " + ofToString(power, 3);

	ofDrawBitmapString(infoString, xoffset, 50);
}

void wezside::SoundManager::setAlgorithm(int key)
{
	algorithm = key;
}

int wezside::SoundManager::getAlgorithm()
{
	return algorithm;
}

void wezside::SoundManager::record()
{
	if (recording) return;
	record_index++;
	if (record_index >= RECORDING_NUM) recording_index = 0;
	recording = true;
}

void wezside::SoundManager::isRecording()
{
	return recording;
}

void wezside::SoundManager::setRecording(bool val)
{
	recording = val;
}

void wezside::SoundManager::setTimecode(int val)
{
	timecode = val;
}

float wezside::SoundManager::getRMSLeft()
{
	return rms_l;
}

float wezside::SoundManager::getRMSRight()
{
	return rms_r;
}

float wezside::SoundManager::getPitchFreq()
{
	return pitch_freq;
}

float wezside::SoundManager::getHFC()
{
	return ofMap(hfc, 0.0, 0.01, 0.0, 0.015);
}

float wezside::SoundManager::getPower()
{
	return power;
}

float wezside::SoundManager::getSmooth()
{
	return smooth;
}

void wezside::SoundManager::setSmooth(float val)
{
	smooth = val;
}