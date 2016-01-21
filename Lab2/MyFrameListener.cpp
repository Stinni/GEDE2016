#include "MyFrameListener.h"

MyFrameListener::MyFrameListener(Ogre::RenderWindow* win)
{
	OIS::ParamList parameters;
	unsigned int windowHandle = 0;
	std::ostringstream windowHandleString;

	win->getCustomAttribute("WINDOW", &windowHandle);
	windowHandleString << windowHandle;

	parameters.insert(std::make_pair("WINDOW", windowHandleString.str()));

	_InputManager = OIS::InputManager::createInputSystem(parameters);

	_Keyboard = static_cast<OIS::Keyboard*>(_InputManager->createInputObject(OIS::OISKeyboard, false));
}

MyFrameListener::~MyFrameListener()
{
	_InputManager->destroyInputObject(_Keyboard);
	OIS::InputManager::destroyInputSystem(_InputManager);
}

bool MyFrameListener::frameStarted(const Ogre::FrameEvent& evt)
{
	_Keyboard->capture();
	if(_Keyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		return false;
	}
	return true;
}
