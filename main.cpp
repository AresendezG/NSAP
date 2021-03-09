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


std::string ToLower(std::string InputStr) {

	std::string StrShiftReg = InputStr;
	int SizeOfStr = InputStr.length();
	int iterator = 0;

	char CurrentLetter;

	try {

		do {
			CurrentLetter = StrShiftReg.at(iterator);
			if (CurrentLetter >= 0x41 && CurrentLetter <= 0x5a) { // Current char is an Uppercase Letter from A to Z
				StrShiftReg.at(iterator) = CurrentLetter + 0x20; // convert to Lower Case
			}
			else if (CurrentLetter == 0x20) //Empty Space
			{
				break;
			}
			iterator++;
		} while (iterator < SizeOfStr);

	}
	catch (std::out_of_range ex) {
		std::cout << "ERROR: Enter a VALID String" << std::endl;
		StrShiftReg = InputStr; // Return Same STR as the input
	}

	return StrShiftReg; // Return converted string
}


int main(int argc, char * args[]) {

	std::cout << "[Command] Simple Audio Player >" << std::endl;

	int fncReturn = -1;
	bool FileLoadedFlag = false;  // Has user selected the File to be played?
	bool AudioOutputFlag = false;  // Has user selected the Audio Output?

	const char* audioDev;
	std::string SelectedOutput, AudioFilePath, Command, cmdLowerCase;
	AudioStuff* AudioObj = new AudioStuff();

	if (AudioObj->InitAudioStuff()) { // Sucessful Init Audio Stuff

		do {
			std::cout << "Type in the Operation > " << std::endl;
			std::getline(std::cin, Command);

			cmdLowerCase = ToLower(Command);

			if (cmdLowerCase == "load") {
				std::cout << "Enter the path of the Audio File > " << std::endl;
				std::getline(std::cin, AudioFilePath);
				if (AudioFilePath.compare("exit") == -1) {
					fncReturn = AudioObj->LoadAudioFile(AudioFilePath.c_str());
					if (fncReturn > 0) {
						std::cout << "Successfully Loaded: " << AudioFilePath << std::endl;
						FileLoadedFlag = true;
					}
					else {
						std::cout << "ERROR: Loading File" << std::endl;
						FileLoadedFlag = false;
					}
				}
				else {
					std::cout << "User Exit cmd" << std::endl;
					return -150;
					//return 0;
				}
			}
			else if (cmdLowerCase == "seloutput") {

				std::cout << "Type the desired Audio Output > " << std::endl;
				std::getline(std::cin, SelectedOutput);
				if (AudioFilePath.compare("exit") == -1) {
					fncReturn = AudioObj->OpenAudioDev(SelectedOutput.c_str());
					if (fncReturn > 0) {
						std::cout << "Successful Open : " << SelectedOutput << std::endl;
						AudioOutputFlag = true;
					}
					else {
						AudioOutputFlag = false;
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
			}

			else if (cmdLowerCase == "availableouts") {
				std::cout << std::endl << "These are the Available Output Device[s]:  " << std::endl;
				AudioObj->DisplayAvailableDevs();
			}
			else if (cmdLowerCase == "play" || cmdLowerCase == "pause" || cmdLowerCase == "stop") { // Playback control

				if (AudioOutputFlag && FileLoadedFlag) { // Can user enter the Playback control?
					if (cmdLowerCase == "play") {
						std::cout << "Now Playing: " << "[" << AudioFilePath << "] >" << std::endl;
						AudioObj->PlaybackControl(1);
					}
					else if (cmdLowerCase == "pause") {
						std::cout << "Paused AudioFile: " << "[" << AudioFilePath << "] >" << std::endl;
						AudioObj->PlaybackControl(2);
					}
					else if (cmdLowerCase == "stop") {
						std::cout << "Playback Stopped: " << "[" << AudioFilePath << "] >" << std::endl;
						AudioObj->PlaybackControl(2);
					}
				}
				else { // No, it must select first the Audio and File
					std::cout << "ERROR: First, Select Audio Out and File to Play" << std::endl;
				}
			}

			else if (cmdLowerCase == "reload") {
				// User picked reload a file, so it must stop execution

				AudioObj->PlaybackControl(2);
				AudioObj->FilePath = "invalid";
				AudioObj->DeviceName = "invalid";
				AudioOutputFlag = false;
				FileLoadedFlag = false;
				std::cout << "RELOAD option Selected, user must pick a new File and Output" << std::endl;
			}

			else if (cmdLowerCase == "exit") {
				break;
			}

			else {
				std::cout << "Type one of the Following Options to Continue" << std::endl;
				std::cout << "[LOAD] to load in Memory a file to be played" << std::endl;
				std::cout << "[SELOUTPUT] to select the desired Audio Output" << std::endl;
				std::cout << "[PLAY], [PAUSE] or [STOP] to Playback Control" << std::endl;
				std::cout << "[AVAILABLEOUTS] to display the Avilable Outputs in this PC" << std::endl;
				std::cout << "[RELOAD] to reset the selected options" << std::endl;
				std::cout << "[EXIT] to exit this SW" << std::endl;
			}


		} while (true);
		return 0;
	}
}