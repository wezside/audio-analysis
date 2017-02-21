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

    // 
    power = audioAnalyzer.getValue(POWER, 0, smooth);



}

void wezside::SoundManager::draw()
{

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

void wezside::SoundManager::record()
{
    if (recording) return;
    if (record_index < NUM_OF_RECORDINGS)
    {
        record_index++;
    }   
    else recording_index = 0;
    recording = true;
}

void wezside::SoundManager::isRecording()
{
    return recording;
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