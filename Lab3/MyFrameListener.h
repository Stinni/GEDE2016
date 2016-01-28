#include "OGRE/OgreRoot.h"
#include "OGRE/OgreSceneManager.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreConfigFile.h"
#include "OGRE/OgreEntity.h"
#include "OIS/OIS.h"

class MyFrameListener : public Ogre::FrameListener
{
private:
	OIS::InputManager* _InputManager;
	OIS::Keyboard* _Keyboard;
	OIS::Mouse* _Mouse;
	Ogre::Camera* _Cam;
	Ogre::SceneNode* _node;
	Ogre::AnimationState* _aniState;
	Ogre::AnimationState* _aniStateTop;
	Ogre::AnimationState* _aniStateDance;
	float _movementspeed;
	float _WalkingSpeed;

public:
	MyFrameListener(Ogre::RenderWindow* win, Ogre::Camera* cam, Ogre::SceneNode* node, Ogre::Entity* ent);
	~MyFrameListener();
	bool frameStarted(const Ogre::FrameEvent& evt);
};
