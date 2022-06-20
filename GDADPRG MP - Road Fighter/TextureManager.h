#pragma once


class TextureManager : sf::NonCopyable
{
// methods
public:
	static TextureManager* getInstance();
	sf::Texture* getTexture(std::string);
	void loadAll();
	void loadSpriteSheet();

private:
	TextureManager() {};

	void loadTexture(std::string, std::string);


// attributes
private:
	std::unordered_map<std::string, sf::Texture*> textureMap;
	static TextureManager* sharedInstance;
};

