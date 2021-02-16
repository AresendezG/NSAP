#include <iostream>
#include <stdio.h>
#include <WS2tcpip.h>
#include <SDL.h>
#include "AudioStuff.h"
#include "CustomTypes.h"


int main(int argc, char * args[]) {


	int PlaybackDevNumber = 0;
	char in = 'x';
	const char* audioDev;
	std::string UserInput;
	AudioStuff* AudioObj = new AudioStuff();


	AudioObj->InitAudioStuff();
	AudioObj->LoadAudioFile("c:\\testfile.wav");
	AudioObj->DisplayAvailableDevs();

	std::cout << "Try to open Audio Device... " << std::endl;
	std::cout << "Enter your Output Dev: " << std::endl;
	std::cin >> UserInput;
	audioDev = UserInput.c_str();
	audioDev = "YourAudio Dev";


	int DevIndex = AudioObj->FindSpecificDev(audioDev);
	int OpenDev = AudioObj->OpenAudioDev(audioDev);
	//AudioObj->OpenAudioDev("");

	
	std::cout << "SW Ready to play, [p] for Play, [a] to Pause and [s] to Stop: " << std::endl;
	while (in != 'q')
	{
		std::cin >> in;
		switch (in)
		{
		case 'p':
			AudioObj->PlaybackControl(1);
			break;
		case 'a':
			AudioObj->PlaybackControl(2);
			break;
		case 's':
			AudioObj->PlaybackControl(3);
			break;
		}
	}
	
	return 0;
}