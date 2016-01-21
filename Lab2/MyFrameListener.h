#include "OGRE/OgreRoot.h"
#include "OGRE/OgreSceneManager.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreConfigFile.h"
#include "OGRE/OgreEntity.h"

class MyFrameListener : public Ogre::FrameListener
{
public:
	MyFrameListener();
	~MyFrameListener();
	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};

