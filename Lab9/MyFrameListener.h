#pragma once
#include "stdafx.h"

#include "OGRE/OgreSceneManager.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreEntity.h"
#include "OIS/OIS.h"
#include "Physics.h"

class MyFrameListener : public Ogre::FrameListener, OIS::MouseListener
{
private:
	OIS::InputManager* _InputManager;
	OIS::Keyboard* _Keyboard;
	OIS::Mouse* _Mouse;
	Ogre::Camera* _Cam;
	Ogre::SceneNode* _node;
	Ogre::SceneManager* _sceneManager;
	Ogre::AnimationState* _aniState;
	Ogre::AnimationState* _aniStateTop;
	Ogre::AnimationState* _aniStateDance;
	Physics* _physicsEngine;
	float _movementspeed;
	float _WalkingSpeed;
	int mouseMask;
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
		mouseMask |= 1 << (int)id;
		return true;
	}
	virtual bool mouseMoved(const OIS::MouseEvent &arg) {
		return true;
	}
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
		return true;
	}

public:
	MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam, Ogre::SceneNode* node,
		Ogre::Entity* ent, Ogre::SceneManager* sceneManager , Physics* physicsEngine);
	~MyFrameListener();
	bool frameStarted(const Ogre::FrameEvent& evt);
};
