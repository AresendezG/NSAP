#include <iostream>
#include <string>
#include <stdio.h>
#include <WS2tcpip.h>
#include <SDL.h>
#include "AudioStuff.h"
#include "CustomTypes.h"

#define FILEPATH "C:\\tmp\\MoodyLoop.wav"

/*
* Simple command-based audio player, using SDL
Author: Esli Alejandro Resendez, 

Requires: SDL2.dll and Environment Variable (Windows)

This software is free to copy and reproduce, but comes with no warranty. 

ARGE Software®, a brand from ARGE Technologies, LLC. 
Feb 2021.

*/


int main(int argc, char * args[]) {

	std::cout << "[Network] Simple Audio Player >" << std::endl;

	int fncReturn = -1;
	char in = 'x';
	const char* audioDev;
	std::string SelectedOutput, AudioFilePath;
	AudioStuff* AudioObj = new AudioStuff();


	if (AudioObj->InitAudioStuff()) { // Make sure SDL stuff can be initd 
			// Load a valid WAV File to be able to play

		do {

			std::cout << "Type the path of the Audio File > " << std::endl;
			std::getline(std::cin, AudioFilePath);
			if (AudioFilePath.compare("exit") == -1) {
				fncReturn = AudioObj->LoadAudioFile(AudioFilePath.c_str());
				if (fncReturn > 0) {
					std::cout << "Successfully Loaded: " << AudioFilePath << std::endl;
				}
			}
			else {
				std::cout << "User Exit cmd" << std::endl;
				return 0;
				//return 0;
			}
		} while (fncReturn < 0);

		fncReturn = -1;

		// Display the Available Audio Outputs 
		std::cout << std::endl << "List of Available Audio Devices:  " << std::endl;
		AudioObj->DisplayAvailableDevs();

		// User picks which Output wants 
		do {

			std::cout << "Type the desired Audio Output > " << std::endl;
			std::getline(std::cin, SelectedOutput);
			if (AudioFilePath.compare("exit") == -1) {
				fncReturn = AudioObj->OpenAudioDev(SelectedOutput.c_str());
				if (fncReturn > 0) {
					std::cout << "Successful Open : " << SelectedOutput << std::endl;
				}
				else {
					std::cout << "ERROR: Unable to Open " << SelectedOutput << std::endl;
					std::cout << "Select a different Output from the Available: " << std::endl;
					AudioObj->DisplayAvailableDevs();
				}
			}
			else {
				std::cout << "User decided to EXIT>" << std::endl;
				return 0;
				//return 0;
			}
		} while (fncReturn < 0);
		//AudioObj->OpenAudioDev("");


		std::cout << "SW Ready to play, [p] for Play, [a] to Pause and [s] to Stop: " << std::endl;
		while (in != 'q')
		{
			std::cin >> in;
			switch (in)
			{
			case 'p':
				std::cout << "Now Playing: " << "[" << AudioFilePath << "] >" << std::endl;
				AudioObj->PlaybackControl(1);
				break;
			case 'a':
				std::cout << "Audio Paused at: " << (int)AudioObj->audio.pos << std::endl;
				AudioObj->PlaybackControl(2);
				break;
			case 's':
				AudioObj->PlaybackControl(3);
				break;
			case 'r':

				break;


			}
		}
	}
	else {
		std::cout << "ERROR: Unable to load SDL Library, Check for SDL2.dll " << std::endl;
		return -1024;
	}
	return 0;
}