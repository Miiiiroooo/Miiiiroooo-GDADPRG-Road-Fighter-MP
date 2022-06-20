#pragma once


class SFXManager : sf::NonCopyable
{
// methods
public:
	static SFXManager* getInstance();
	void loadAll();
	sf::SoundBuffer* getAudio(std::string);

private:
	SFXManager() {};

	void loadAudio(std::string, std::string);


// attributes
private:
	std::unordered_map<std::string, sf::SoundBuffer*> audioMap;
	static SFXManager* sharedInstance;
};