#include "MyApplication.h"

MyApplication::MyApplication()
{
	_sceneManager = NULL;
	_root = NULL;
	_listener = NULL;
}

MyApplication::~MyApplication()
{
	delete _root;
	delete _listener;
}

void MyApplication::loadResources()
{
	Ogre::String sectionName, typeName, dataName;
	Ogre::ConfigFile cf;
	cf.load("../LabFiles/OgreConfig/resources_d.cfg");
	Ogre::ConfigFile::SectionIterator sectionIter = cf.getSectionIterator();

 	while(sectionIter.hasMoreElements()) {
		sectionName = sectionIter.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = sectionIter.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for( i = settings->begin() ; i != settings->end() ; ++i ) {
			typeName = i->first;
			dataName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataName, typeName, sectionName);
		}
	}

 	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

int MyApplication::startup()
{
	_root = new Ogre::Root("../LabFiles/OgreConfig/plugins_d.cfg","../LabFiles/OgreConfig/ogre.cfg");

	if(!_root->showConfigDialog()) {
		return -1;
	}

	Ogre::RenderWindow* window = _root->initialise(true, "Ogre3D Beginners Guide - Lab8");

	_sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);
	Ogre::Camera* camera = _sceneManager->createCamera("Camera");

	camera->setPosition(Ogre::Vector3(0,0,50));
	camera->lookAt(Ogre::Vector3(0,0,0));
	camera->setNearClipDistance(5);

	Ogre::Viewport* viewport = window->addViewport(camera);
	viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
	camera->setAspectRatio(Ogre::Real(viewport->getActualWidth())/Ogre::Real(viewport->getActualHeight()));

	loadResources();
	createScene();
	_listener = new MyFrameListener(window, camera, _SinbadNode, _SinbadEnt);
	_root->addFrameListener(_listener);

	return 0;
}

void MyApplication::createScene()
{
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -5);
	Ogre::MeshManager::getSingleton().createPlane("plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* ground = _sceneManager->createEntity("LightPlaneEntity", "plane");
	_SinbadEnt = _sceneManager->createEntity("Sinbad.mesh");
	//printAnimations(_SinbadEnt);
	_SinbadNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
	_SinbadNode->attachObject(_SinbadEnt);

	/*Ogre::ParticleSystem* _partSystem1 = _sceneManager->createParticleSystem("smoke", "MySmoke1");
	Ogre::SceneNode* _smokeNode1 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(50,50,50));
	_smokeNode1->attachObject(_partSystem1);*/

	Ogre::ParticleSystem* _partSystem2 = _sceneManager->createParticleSystem("snow", "MySnow");
	Ogre::SceneNode* _snowNode = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0,0,0));
	_snowNode->attachObject(_partSystem2);

	Ogre::ParticleSystem* _partSystem3 = _sceneManager->createParticleSystem("fountain", "MyFountain");
	Ogre::SceneNode* _fountainNode = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-50,0,-50));
	_fountainNode->attachObject(_partSystem3);

	/*Ogre::ParticleSystem* _partSystem4 = _sceneManager->createParticleSystem("fountain2", "Examples/PurpleFountain");
	Ogre::SceneNode* _fountainNode2 = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(50,0,-50));
	_fountainNode2->attachObject(_partSystem4);*/

	_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ground);
	ground->setMaterialName("Examples/BeachStones");

	Ogre::Light* light = _sceneManager->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1, -1, 0));
	_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	_sceneManager->setAmbientLight(Ogre::ColourValue(.3f,.3f,.3f));

	Ogre::Light* plight = _sceneManager->createLight("Light2");
	plight->setType(Ogre::Light::LT_POINT);
}

void MyApplication::renderOneFrame()
{
	Ogre::WindowEventUtilities::messagePump();
	_keepRunning = _root->renderOneFrame();
}

bool MyApplication::keepRunning()
{
	return _keepRunning;
}

void MyApplication::printAnimations(Ogre::Entity* ent)
{
	// Print out all available animation names for _SinbadEnt.
	Ogre::AnimationStateIterator iter = ent->getAllAnimationStates()->getAnimationStateIterator();
	while (iter.hasMoreElements()) {
		Ogre::AnimationState *a = iter.getNext();
		std::cout << a->getAnimationName() << std::endl;
	}
}
