#include "stdafx.h"
#include "SFXManager.h"


// static declarations of the SFXManager Class
SFXManager* SFXManager::sharedInstance = NULL;

SFXManager* SFXManager::getInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new SFXManager;

	return sharedInstance;
}


// public methods of the SFXManager Class
void SFXManager::loadAll()
{
	std::string key, path;
	std::ifstream inFile;

	inFile.open("Media/Additional Files/LoadAudio.txt");

	if (!inFile)
	{
		std::cerr << "Unable to open the LoadAudio.txt\n\nClosing Window..." << std::endl;
	}
	else
		while (inFile >> key >> path)
			loadAudio(key, path);


	inFile.close();
}


sf::SoundBuffer* SFXManager::getAudio(std::string key)
{
	if (audioMap[key] != NULL)
		return audioMap[key];
	else
	{
		std::cout << "No audio found for " << key << std::endl;
		return NULL;
	}
}


// private methods of the SFXManager Class
void SFXManager::loadAudio(std::string key, std::string path)
{
	sf::SoundBuffer* soundBuffer = new sf::SoundBuffer;

	soundBuffer->loadFromFile(path);
	audioMap[key] = soundBuffer;
}