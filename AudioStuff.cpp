#include <iostream>
#include "AudioStuff.h"
#include "CustomTypes.h"


void AudioStuff() {

	SDL_Init(SDL_INIT_EVERYTHING);
	std::cout << "SDL Loaded" << std::endl;
	//return;

}

void AudioStuff::InitAudioStuff() {

	SDL_Init(SDL_INIT_EVERYTHING);

	return;
}

void AudioStuff::AudioCallback(void* userdata, Uint8* stream, int streamLength) {
	
	AudioData* audio = (AudioData*)userdata;

	if (audio->length == 0) {
		return;
	}

	Uint32 length = (Uint32)streamLength;

	length = (length > audio->length ? audio->length : length);

	SDL_memcpy(stream, audio->pos, length);

	audio->pos += length;
	audio->length -= length;

}

void AudioStuff::DisplayAvailableDevs() {
	
	int count = SDL_GetNumAudioDevices(0);

	for (int i = 0; i < count; ++i)
	{
		std::cout << "Device " << i << ": " << SDL_GetAudioDeviceName(i, 0) << std::endl;
		
	}
}

int AudioStuff::FindSpecificDev(const char* DevToFind) {
	/* Will check if a given Audio Device is listed in the system, if so will return the index */

	int count = SDL_GetNumAudioDevices(0);
	for (int i = 0; i < count; ++i)
	{
		int result = std::strcmp(DevToFind, SDL_GetAudioDeviceName(i, 0));
			if (result != -1) {
				return i;
		}
			

	}
	return -1;

}

int AudioStuff::LoadAudioFile(const char* AudioFilePath) {
	

	if (SDL_LoadWAV(AudioFilePath, &wavSpec, &wavStart, &wavLength) == NULL)
	{
		std::cerr << "Could not load file!" << std::endl;
		return -1;
	}
	else 
	{
		std::cout << "Successull Load! " << std::endl;
		return 1;
	}
		
}

int AudioStuff::OpenAudioDev(const char* AudioDeviceToOpen) {

	audio.pos = wavStart;
	audio.length = wavLength;
	wavSpec.callback = AudioCallback;
	wavSpec.userdata = &audio;

	device = SDL_OpenAudioDevice(AudioDeviceToOpen, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

	if (device == 0) {
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		return -2;
	}
	else
		return 1;

}

void AudioStuff::PlaybackControl(int Opt) {

	switch (Opt) {
	case 1: // Play (Zero to unpause, or play)
		SDL_PauseAudioDevice(device, 0);
		break;
	case 2: // Pause (NonZero to pause)
		SDL_PauseAudioDevice(device, 1);
		break;
	case 3: // Pause playing, and return to start position
		SDL_PauseAudioDevice(device, 1);
		audio.pos = wavStart;
		break;
	default:
		std::cout << "Default Opt" << std::endl;
		break;
	}

}

 AudioStuff::~AudioStuff() {

	 SDL_CloseAudioDevice(device);
	 SDL_FreeWAV(wavStart);
	 SDL_Quit();
}