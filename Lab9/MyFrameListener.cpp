#include "stdafx.h"
#include "MyFrameListener.h"

MyFrameListener::MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam, Ogre::SceneNode* node,
								 Ogre::Entity* ent, Ogre::SceneManager* sceneManager , Physics* physicsEngine)
{
	_Cam = cam;
	_node = node;
	_sceneManager = sceneManager;
	_physicsEngine = physicsEngine;
	_movementspeed = 20.0f;
	_WalkingSpeed = 20.0f;
	mouseMask = 0;
	OIS::ParamList parameters;
	unsigned int windowHandle = 0;
	std::ostringstream windowHandleString;

	win->getCustomAttribute("WINDOW", &windowHandle);
	windowHandleString << windowHandle;
	parameters.insert(std::make_pair("WINDOW", windowHandleString.str()));

	_InputManager = OIS::InputManager::createInputSystem(parameters);
	_Keyboard = static_cast<OIS::Keyboard*>(_InputManager->createInputObject(OIS::OISKeyboard, false));
	// 7.3 Initialize the Mouse input listener.
	try {
		_Mouse = static_cast<OIS::Mouse*>(_InputManager->createInputObject(OIS::OISMouse, true));
		_Mouse->setEventCallback(this);
		std::cout << "Successfuly created Mouse";
	}
	catch (...) {
		std::cout << "Failed to initialize Mouse";
		_Mouse = 0;
	}

	_aniState = ent->getAnimationState("RunBase");
	_aniState->setLoop(false);
	_aniStateTop = ent->getAnimationState("RunTop");
	_aniStateTop->setLoop(false);
}

MyFrameListener::~MyFrameListener()
{
	_InputManager->destroyInputObject(_Keyboard);
	_InputManager->destroyInputObject(_Mouse);
	OIS::InputManager::destroyInputSystem(_InputManager);
}

bool MyFrameListener::frameStarted(const Ogre::FrameEvent& evt)
{
	_Keyboard->capture();
	mouseMask = 0;
	_Mouse->capture();

	if (  (mouseMask & (1 << (int)OIS::MouseButtonID::MB_Left))  ) {
		// Create a cube entity.
		Ogre::Entity* cubeEnt = _sceneManager->createEntity("Cube.mesh");
		Ogre::SceneNode* cubeNode = _sceneManager->getRootSceneNode()->createChildSceneNode();

		cubeNode->setScale(0.005f, 0.005f, 0.005f);
		// Set the position of the cube to the front of the origin of the camera 
		cubeNode->setPosition(_Cam->getPosition() + _Cam->getDirection());
		cubeNode->attachObject(cubeEnt);

		// Now make the cube a rigid body, give it some linearVelocity and add it to the physics world
		btRigidBody* boxBody = _physicsEngine->AddDynamicCubeRigidBody(cubeNode, cubeEnt, 2);
		boxBody->setLinearVelocity(btVector3(_Cam->getDirection().x, _Cam->getDirection().y, _Cam->getDirection().z) * 30);
	}

	Ogre::Vector3 SinbadTranslate(0, 0, 0);
	float rotX = _Mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
	float rotY = _Mouse->getMouseState().Y.rel * evt.timeSinceLastFrame* -1;
	float _rotation = 0.0f;
	bool walked = false;

	if(_Keyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		return false;
	}
	Ogre::Vector3 translate(0, 0, 0);
	if(_Keyboard->isKeyDown(OIS::KC_UP))
	{
		translate += Ogre::Vector3(0, 0, -1);
	}
	if(_Keyboard->isKeyDown(OIS::KC_DOWN))
	{
		translate += Ogre::Vector3(0, 0, 1);
	}
	if(_Keyboard->isKeyDown(OIS::KC_LEFT))
	{
		translate += Ogre::Vector3(-1, 0, 0);
	}
	if(_Keyboard->isKeyDown(OIS::KC_RIGHT))
	{
		translate += Ogre::Vector3(1, 0, 0);
	}
	if(_Keyboard->isKeyDown(OIS::KC_W))
	{
		SinbadTranslate += Ogre::Vector3(0, 0, -1);
		_rotation = 3.14f;
		walked = true;
	}
	if(_Keyboard->isKeyDown(OIS::KC_S))
	{
		SinbadTranslate += Ogre::Vector3(0, 0, 1);
		_rotation = 0.0f;
		walked = true;
	}
	if(_Keyboard->isKeyDown(OIS::KC_A))
	{
		SinbadTranslate += Ogre::Vector3(-1, 0, 0);
		_rotation = -1.57f;
		walked = true;
	}
	if(_Keyboard->isKeyDown(OIS::KC_D))
	{
		SinbadTranslate += Ogre::Vector3(1, 0, 0);
		_rotation = 1.57f;
		walked = true;
	}

	if(walked)
	{
		_aniState->setEnabled(true);
		_aniStateTop->setEnabled(true);
		if(_aniState->hasEnded())
		{
			_aniState->setTimePosition(0.0f);
		}
		if(_aniStateTop->hasEnded())
		{
			_aniStateTop->setTimePosition(0.0f);
		}
	}
	else
	{
		_aniState->setTimePosition(0.0f);
		_aniState->setEnabled(false);
		_aniStateTop->setTimePosition(0.0f);
		_aniStateTop->setEnabled(false);
	}

	_aniState->addTime(evt.timeSinceLastFrame);
	_aniStateTop->addTime(evt.timeSinceLastFrame);

	_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);
	_Cam->yaw(Ogre::Radian(rotX));
	_Cam->pitch(Ogre::Radian(rotY));

	_node->translate(SinbadTranslate * evt.timeSinceLastFrame * _WalkingSpeed);
	_node->resetOrientation();
	_node->yaw(Ogre::Radian(_rotation));

	_physicsEngine->getDynamicsWorld()->stepSimulation(evt.timeSinceLastFrame);

	return true;
}
