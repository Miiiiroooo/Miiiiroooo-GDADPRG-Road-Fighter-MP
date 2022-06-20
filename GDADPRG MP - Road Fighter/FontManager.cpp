#include "stdafx.h"
#include "FontManager.h"


// static declarations of the FontManager Class
FontManager* FontManager::sharedInstance = NULL;

FontManager* FontManager::getInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new FontManager();

	return sharedInstance;
}


// public methods of the FontManager Class
void FontManager::loadAll()
{
	loadFont("default", "Media/Fonts/ArcadeClassic.ttf");
}


sf::Font* FontManager::getFont(std::string key)
{
	if (fontMap[key] != NULL)
	{
		return fontMap[key];
	}
	else
	{
		std::cout << "No font found for: " << key;
		return NULL;
	}
}


// Private Methods of the FontManager Class 
void FontManager::loadFont(std::string key, std::string path)
{
	sf::Font* font = new sf::Font();
	font->loadFromFile(path);
	fontMap[key] = font;
}