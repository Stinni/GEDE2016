#include "MyFrameListener.h"

MyFrameListener::MyFrameListener(void)
{
}

MyFrameListener::~MyFrameListener(void)
{
}

bool MyFrameListener::frameStarted(const Ogre::FrameEvent& evt)
{
	return false;
}

bool MyFrameListener::frameEnded(const Ogre::FrameEvent& evt)
{
	return false;
}

bool MyFrameListener::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return false;
}
