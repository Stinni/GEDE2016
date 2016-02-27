#pragma once
#include "MyApplication.h"
#include "MyFrameListener.h"
#include "CylindricalEffect.h"

class MyApplication
{
private:
	Ogre::SceneManager* _sceneManager;
	Ogre::Root* _root;
	Ogre::Entity* _SinbadEnt;
	Ogre::Entity* _myCube;
	Ogre::SceneNode* _SinbadNode;
	Ogre::SceneNode* cubenode;
	Ogre::ManualObject* manual;
	Ogre::StaticGeometry* _field;
	MyFrameListener* _listener;
	CylindricalEffect* _ceffect;
	bool _keepRunning;

public:
	MyApplication();
	~MyApplication();
	void loadResources();
	int startup();
	void createScene();
	void renderOneFrame();
	bool keepRunning();
	void printAnimations(Ogre::Entity* ent);
	void createGrass();
};
