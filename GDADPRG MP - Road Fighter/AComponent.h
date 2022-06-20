#pragma once

class AGameObject;

class AComponent
{
// enum declaration
public:
	enum ComponentType {
		NotSet = -1,
		Script = 0,
		Renderer = 1,
		Input = 2,
		Physics = 3
	};


// methods
public:
	AComponent(std::string name, ComponentType type);
	virtual ~AComponent();

	void attachOwner(AGameObject* owner);
	void detachOwner();
	AGameObject* getOwner();
	ComponentType getType();
	std::string getName();

	void setDeltaTime(sf::Time deltaTime);
	virtual void perform() = 0;


// attributes
protected:
	AGameObject* owner;
	ComponentType type;
	std::string name;
	sf::Time deltaTime;
};

