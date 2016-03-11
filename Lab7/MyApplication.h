#pragma once
#include "MyApplication.h"
#include "MyFrameListener.h"

class MyApplication
{
private:
	Ogre::SceneManager* _sceneManager;
	Ogre::Root* _root;
	Ogre::Entity* _SinbadEnt;
	Ogre::SceneNode* _SinbadNode;
	MyFrameListener* _listener;
	bool _keepRunning;

public:
	MyApplication();
	~MyApplication();
	void loadResources();
	int startup();
	void createScene();
	void renderOneFrame();
	bool keepRunning();
};
