#pragma once

#include "AComponent.h"
#include "Renderer.h"
#include "GenericInputController.h"
#include "TextureManager.h"

class AGameObject
{
// methods
public:
	AGameObject(std::string name);
	virtual ~AGameObject();
	std::string getName();

	// Game related methods
	virtual void initialize() = 0;
	virtual void processInputs(sf::Event event);
	virtual void update(sf::Time deltaTime);
	virtual void draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);
	void setEnabled(bool flag);
	bool isEnabled();

	// SFML related methods
	sf::Sprite* getSprite();
	sf::Transformable* getTransformable();
	sf::Transform getGlobalTransform();

	// parent-child related methods
	void attachChild(AGameObject* child);
	void detachChild(AGameObject* child);
	void setParent(AGameObject* parent);
	AGameObject* getParent();
	void setPosition(float x, float y);

	// component related methods
	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);
	AComponent* findComponentByName(std::string name);
	AComponent* findComponentByType(AComponent::ComponentType type, std::string name);
	std::vector<AComponent*> getComponentsOfType(AComponent::ComponentType type);
	std::vector<AComponent*> getComponentsOfTypeRecursive(AComponent::ComponentType type);

private:
	std::vector<AComponent*> getComponentRecursiveProper(AGameObject* object, AComponent::ComponentType type, std::vector<AComponent*> foundList);


// attributes
protected:
	std::string name;
	sf::Sprite* sprite;
	sf::Texture* texture;
	sf::Transformable transformable;

	AGameObject* parent;
	std::vector<AGameObject*> childList;
	std::vector<AComponent*> componentList;

private:
	bool enabled = true;
};

