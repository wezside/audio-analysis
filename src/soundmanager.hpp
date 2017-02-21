#ifndef __SOUNDMANAGER_HPP__
#define __SOUNDMANAGER_HPP__

#include "ofMain.h"
#include "ofxAudioAnalyzer.h"

namespace wezside
{
	class SoundManager
	{
		private:
			ofSoundStream soundStream;
        	ofxAudioAnalyzer audioAnalyzer;

        	// Algorithms
        	float rms_l, rms_r;
        	float pitch_freq;
        	float hfc;
        	float smooth;
        	float power;

        	float recording_1[1000];
        	float recording_2[1000];
        	float recording_3[1000];
        	float recording_4[1000];
        	float recording_5[1000];

        	int recording_index;

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