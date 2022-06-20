#pragma once

class FontManager : sf::NonCopyable
{
public:
	static FontManager* getInstance();

	void loadAll();
	sf::Font* getFont(std::string);

private:
	FontManager() {};
	void loadFont(std::string, std::string);


private:
	static FontManager* sharedInstance;
	std::unordered_map<std::string, sf::Font*> fontMap;
};