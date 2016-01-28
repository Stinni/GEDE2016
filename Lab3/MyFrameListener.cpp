#include "MyFrameListener.h"

MyFrameListener::MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam, Ogre::SceneNode* node, Ogre::Entity* ent)
{
	_Cam = cam;
	_node = node;
	_movementspeed = 50.0f;
	_WalkingSpeed = 50.0f;
	OIS::ParamList parameters;
	unsigned int windowHandle = 0;
	std::ostringstream windowHandleString;

	win->getCustomAttribute("WINDOW", &windowHandle);
	windowHandleString << windowHandle;
	parameters.insert(std::make_pair("WINDOW", windowHandleString.str()));

	_InputManager = OIS::InputManager::createInputSystem(parameters);
	_Keyboard = static_cast<OIS::Keyboard*>(_InputManager->createInputObject(OIS::OISKeyboard, false));
	_Mouse = static_cast<OIS::Mouse*>(_InputManager->createInputObject(OIS::OISMouse, false));

	_aniState = ent->getAnimationState("RunBase");
	_aniState->setLoop(false);
	_aniStateTop = ent->getAnimationState("RunTop");
	_aniStateTop->setLoop(false);
	_aniStateDance = ent->getAnimationState("Dance");
	_aniStateDance->setLoop(true);
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
	_Mouse->capture();

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
		_aniStateDance->setTimePosition(0.0f);
		_aniStateDance->setEnabled(false);
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
		_aniStateDance->setEnabled(true);
		if(_aniStateDance->hasEnded())
		{
			_aniStateDance->setTimePosition(0.0f);
		}
	}

	_aniState->addTime(evt.timeSinceLastFrame);
	_aniStateTop->addTime(evt.timeSinceLastFrame);
	_aniStateDance->addTime(evt.timeSinceLastFrame);

	_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);
	_Cam->yaw(Ogre::Radian(rotX));
	_Cam->pitch(Ogre::Radian(rotY));

	_node->translate(SinbadTranslate * evt.timeSinceLastFrame * _WalkingSpeed);
	_node->resetOrientation();
	_node->yaw(Ogre::Radian(_rotation));

	return true;
}
