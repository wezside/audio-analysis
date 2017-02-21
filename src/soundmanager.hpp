#ifndef __SOUNDMANAGER_HPP__
#define __SOUNDMANAGER_HPP__

#include "ofMain.h"
#include "ofxAudioAnalyzer.h"

#define RECORDING_NUM 5
#define RECORDING_SIZE 1000

namespace wezside
{
	class SoundManager
	{
		private:
			ofSoundStream soundStream;
        	ofxAudioAnalyzer audioAnalyzer;
        	ofColor colors[RECORDING_NUM];

        	// Algorithms
        	float rms_l, rms_r;
        	float pitch_freq;
        	float hfc;
        	float smooth;
        	float power;

        	float recording[RECORDING_NUM][RECORDING_SIZE];

        	int timecode;
        	int recording_index;
        	int algorithm;
        	int data_index;

        	bool recording;

		public:
			// Default constructor
			SoundManager()
			{
				recording = false;
				recording_index = 0;

			}

			// Copy constructor
			SoundManager (const SoundManager& s) {}

			// Copy assignment constructor
			SoundManager& operator=(SoundManager& s) 
			{ 
				return *this;
			};

			// Destructor
			virtual ~SoundManager() {}	

			void setup(ofBaseApp *app);
			void analyze(ofSoundBuffer &inBuffer);
			void update();
			void draw();
			void exit();

			void record();
			void isRecording();
			void setRecording(bool val);
			void setAlgorithm(int key);
			int getAlgorithm();

			float getRMSLeft();
			float getRMSRight();
			float getPitchFreq();
        	float getHFC();
        	float getPower();


			float getSmooth();
			void setSmooth(float val);
	};
}
#endif //__SOUNDMANAGER_HPP__