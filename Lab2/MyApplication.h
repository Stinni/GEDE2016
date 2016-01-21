#include "OGRE/OgreRoot.h"
#include "OGRE/OgreSceneManager.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreConfigFile.h"
#include "OGRE/OgreEntity.h"
#include "OGRE/OgreWindowEventUtilities.h"
#include "OGRE/OgreMeshManager.h"
#include "MyFrameListener.h"

class MyApplication
{
private:
	Ogre::SceneManager* _sceneManager;
	Ogre::Root* _root;
	Ogre::SceneNode* _SinbadNode;
	Ogre::Entity* _SinbadEnt;
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
	void printAnimations(Ogre::Entity* ent);
};
