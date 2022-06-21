#include "stdafx.h"
#include "TextureManager.h"
#include <iostream>

using namespace std;

// static declarations of the TextureManager Class
TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance()
{
	if (sharedInstance == NULL)
		sharedInstance = new TextureManager();

	return sharedInstance;
}


// public methods of the TextureManager Class
sf::Texture* TextureManager::getTexture(std::string key)
{
	if (textureMap[key] != NULL)
		return textureMap[key];
	else
	{
		std::cout << "No texture found for " << key << std::endl;
		return NULL;
	}
}


void TextureManager::loadAll()
{
	std::string key, path;
	std::ifstream inFile;

	inFile.open("Media/Additional Files/LoadAdditionalTextures.txt");

	if (!inFile)
	{
		std::cerr << "Unable to open the LoadAdditionalTextures.txt\n\nClosing Window..." << std::endl;
	}
	else
	{
		while (inFile >> key >> path)
			loadTexture(key, path);
	}

	inFile.close();
}


void TextureManager::loadSpriteSheet()
{
	// init json file and parse its data
	FILE* inFile = fopen("Media/Additional Files/RoadFighterSpriteSheet.json", "rb");

	char readBuffer[65536];
	rapidjson::FileReadStream jsonFile(inFile, readBuffer, sizeof(readBuffer));
	rapidjson::Document doc;

	doc.ParseStream(jsonFile);
	fclose(inFile);


	// initialize new sprite while obtaining the values of the parsed data
	for (rapidjson::Value::ConstMemberIterator itr = doc["frames"].MemberBegin(); itr != doc["frames"].MemberEnd(); ++itr)
	{
		// init rect for each sprite in sprite sheet
		int x = itr->value["frame"]["x"].GetInt();
		int y = itr->value["frame"]["y"].GetInt();
		int width = itr->value["frame"]["w"].GetInt();
		int height = itr->value["frame"]["h"].GetInt();
		sf::Rect<int> rect(x, y, width, height);


		// init texture from file with specified rect
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile("Media/Textures/RoadFighterSpriteSheet.png", rect);  // takes more time to load up
		textureMap[itr->name.GetString()] = texture;

	}
}


// private methods of the TextureManager Class
void TextureManager::loadTexture(std::string key, std::string path)
{
	sf::Texture* texture = new sf::Texture;

	texture->loadFromFile(path);
	textureMap[key] = texture;
}