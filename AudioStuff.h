#include <iostream>
#include <SDL.h>
#include "CustomTypes.h"
#pragma once


class AudioStuff
{
public:
	// Attributes
	std::string FilePath; // WAV File to be loaded
	std::string DeviceName; // Generic name of the device to be used as output
	AudioData audio;

	SDL_AudioSpec wavSpec;
	Uint8* wavStart;
	Uint32 wavLength;
	const char* AudioFilename;
	const char* OutputName;
	
	// Methods
	bool InitAudioStuff();
	static void AudioCallback(void* userdata, Uint8* stream, int streamLength);
	int LoadAudioFile(const char* AudioFilePath);
	void DisplayAvailableDevs();
	int OpenAudioDev(const char* AudioDeviceToOpen);
	void PlaybackControl(int Opt);
	int FindSpecificDev(const char* DevToFind);
	~AudioStuff();
	//void 

private:
	// Attributes
	SDL_AudioDeviceID device;
	bool isFileLoaded;
	// Methods

};

