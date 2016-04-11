#pragma once
#include "stdafx.h"

#include "OGRE/OgreRoot.h"
#include "OGRE/OgreSceneManager.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreConfigFile.h"
#include "OGRE/OgreEntity.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreMeshManager.h"
#include "OGRE/OgreMath.h"
#include "MyApplication.h"
#include "MyFrameListener.h"
#include "Physics.h"

class MyApplication
{
private:
	Ogre::SceneManager* _sceneManager;
	Ogre::Root* _root;
	Ogre::Entity* _SinbadEnt;
	Ogre::Entity* _myCube;
	Ogre::SceneNode* _SinbadNode;
	Ogre::SceneNode* cubenode;
	MyFrameListener* _listener;
	Physics* _physicsEngine;
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
