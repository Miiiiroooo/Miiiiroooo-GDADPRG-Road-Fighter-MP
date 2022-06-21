#include "stdafx.h"
#include "AGameObject.h"
#include <vector>

using namespace std;


// constructor and destructor of the AGameObject Class
AGameObject::AGameObject(std::string name)
{
	this->name = name;
	this->parent = NULL;
}


AGameObject::~AGameObject()
{
	for (size_t i = 0; i < this->childList.size(); i++)
	{
		delete this->childList[i];
	}

	for (size_t i = 0; i < this->componentList.size(); i++)
	{
		delete this->componentList[i];
	}

	this->childList.clear(); 
	this->childList.shrink_to_fit();
	this->componentList.clear(); 
	this->componentList.shrink_to_fit();

	if (this->parent != NULL)
		this->parent = NULL;
	if (this->sprite != NULL)
		this->sprite = NULL;
		delete this->sprite;
	if (this->texture != NULL)
		delete this->texture;
}


// public methods of the AGameObject Class
std::string AGameObject::getName()
{
	return this->name;
}


void AGameObject::processInputs(sf::Event event)
{
	if (this->isEnabled())
	{
		std::vector<AComponent*> componentList = this->getComponentsOfType(AComponent::ComponentType::Input);

		for (size_t i = 0; i < componentList.size(); i++)
		{
			GenericInputController* inputController = (GenericInputController*)componentList[i];
			inputController->assignEvent(event);
			inputController->perform();
		}

		for (size_t i = 0; i < this->childList.size(); i++)
		{
			this->childList[i]->processInputs(event);
		}
	}
}


void AGameObject::update(sf::Time deltaTime)
{
	if (this->isEnabled())
	{
		std::vector<AComponent*> componentList = this->getComponentsOfType(AComponent::ComponentType::Script);

		for (size_t i = 0; i < componentList.size(); i++)
		{
			componentList[i]->setDeltaTime(deltaTime);
			componentList[i]->perform();
		}


		for (size_t i = 0; i < childList.size(); i++)
		{
			childList[i]->update(deltaTime);
		}
	}
}


void AGameObject::draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
	if (this->isEnabled())
	{
		std::vector<AComponent*> componentList = this->getComponentsOfType(AComponent::ComponentType::Renderer);
		renderStates.transform *= this->transformable.getTransform();

		for (size_t i = 0; i < componentList.size(); i++)
		{
			Renderer* renderer = (Renderer*)componentList[i];
			renderer->assignTargetWindow(targetWindow);
			renderer->setRenderStates(renderStates);
			renderer->perform();
		}

		for (size_t i = 0; i < childList.size(); i++)
		{
			this->childList[i]->draw(targetWindow, renderStates);
		}
	}
}


void AGameObject::setEnabled(bool flag)
{
	this->enabled = flag;
}


bool AGameObject::isEnabled()
{
	return this->enabled;
}


sf::Sprite* AGameObject::getSprite()
{
	return this->sprite;
}


sf::Transformable* AGameObject::getTransformable()
{
	return &this->transformable;
}


sf::Transform AGameObject::getGlobalTransform()
{
	//cout << "GetGlobalTransform of: " << this->getName() << endl;
	AGameObject* parentObj = this;
	vector<AGameObject*> parentList;
	while (parentObj != NULL)
	{
		parentList.push_back(parentObj);
		parentObj = parentObj->getParent();
	}

	sf::Transform transform = sf::Transform::Identity;
	int startIdx = parentList.size() - 1;
	for (int i = startIdx; i >= 0; i--)
	{
		transform = transform * parentList[i]->getTransformable()->getTransform();
	}
	return transform;
}


void AGameObject::attachChild(AGameObject* child)
{
	this->childList.push_back(child);
	child->initialize();
}


void AGameObject::detachChild(AGameObject* child)
{
	int index = -1;

	for (size_t i = 0; i < this->childList.size(); i++)
		if (this->childList[i] == child)
			index = (int)i;

	if (index != -1)
		this->childList.erase(this->childList.begin() + index);
}


void AGameObject::setParent(AGameObject* parent)
{
	this->parent = parent;
}


AGameObject* AGameObject::getParent()
{
	return this->parent;
}


void AGameObject::setPosition(float x, float y)
{
	this->transformable.setPosition(x, y);
}


void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}


void AGameObject::detachComponent(AComponent* component)
{
	int index = -1;

	for (size_t i = 0; i < this->componentList.size(); i++)
	{
		if (this->componentList[i] == component)
		{
			index = (int)i;
			this->componentList[i]->detachOwner();
			break;
		}
	}

	if (index != -1)
	{
		this->componentList.erase(this->componentList.begin() + index);
	}
}


AComponent* AGameObject::findComponentByName(std::string name)
{
	for (size_t i = 0; i < componentList.size(); i++)
		if (this->componentList[i]->getName() == name)
			return this->componentList[i];

	return NULL;
}


AComponent* AGameObject::findComponentByType(AComponent::ComponentType type, std::string name)
{
	for (size_t i = 0; i < componentList.size(); i++)
		if (this->componentList[i]->getType() == type && this->componentList[i]->getName() == name)
			return this->componentList[i];

	return NULL;
}


// returns all components of a given type
std::vector<AComponent*> AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
	std::vector<AComponent*> foundList;

	for (size_t i = 0; i < this->componentList.size(); i++)
		if (this->componentList[i]->getType() == type)
			foundList.push_back(this->componentList[i]);

	return foundList;
}


//recursive implementation; also searches through its children
std::vector<AComponent*> AGameObject::getComponentsOfTypeRecursive(AComponent::ComponentType type)
{
	std::vector<AComponent*> foundList;

	for (size_t i = 0; i < this->componentList.size(); i++)
		if (this->componentList[i]->getType() == type)
			foundList.push_back(this->componentList[i]);

	for (size_t i = 0; i < childList.size(); i++)
		foundList = this->getComponentRecursiveProper(this->childList[i], type, foundList);

	return foundList;
}



std::vector<AComponent*> AGameObject::getComponentRecursiveProper(AGameObject* object, AComponent::ComponentType type, std::vector<AComponent*> foundList)
{
	return foundList;
}