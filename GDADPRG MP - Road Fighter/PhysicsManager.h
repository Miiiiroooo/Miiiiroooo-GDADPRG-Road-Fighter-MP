#pragma once

#include "Collider.h"

typedef std::vector<Collider*> CollisionList;

class PhysicsManager : public AComponent
{
// methods
public:
	static void initialize(std::string name, AGameObject* parent);
	static void destroy();
	static PhysicsManager* getInstance();
	~PhysicsManager() {};

	void trackObject(Collider* object);
	void untrackObject(Collider* object);
	void perform();

private:
	PhysicsManager(std::string name) : AComponent(name, Script) {};
	PhysicsManager(PhysicsManager const&) : AComponent(name, Script) {};
	PhysicsManager& operator=(PhysicsManager const&) {};

	void cleanUpObjects();


// attributes
private:
	static PhysicsManager* sharedInstance;
	CollisionList trackedObjects;
	CollisionList forCleaningObjects;
};

