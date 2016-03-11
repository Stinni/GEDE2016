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

	Ogre::RenderWindow* window = _root->initialise(true, "Ogre3D Beginners Guide - Lab7");

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
	Ogre::Entity* _ground = _sceneManager->createEntity("LightPlaneEntity", "plane");
	Ogre::Plane water(Ogre::Vector3::UNIT_Y, 0.0f);
	Ogre::MeshManager::getSingleton().createPlane("AnimatedWater", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		water, 30, 30, 40, 40, true, 1, 10, 10, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* waterEnt = _sceneManager->createEntity("waterEntity", "AnimatedWater");
	waterEnt->setMaterialName("shader/timeTexture");
	_sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, -40))->attachObject(waterEnt);
	Ogre::Entity* _sphereEnt = _sceneManager->createEntity("mySphere", Ogre::SceneManager::PT_SPHERE);
	_sphereEnt->setMaterialName("shader/lighting");
	Ogre::SceneNode* _sphereNode = _sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, 40));
	_sphereNode->attachObject(_sphereEnt);
	_sphereNode->setScale(Ogre::Vector3(.1f, .1f, .1f));

	_SinbadEnt = _sceneManager->createEntity("Sinbad.mesh");
	_SinbadNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
	_SinbadNode->attachObject(_SinbadEnt);
	
	_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(_ground);
	_ground->setMaterialName("shader/texture");
	//_SinbadEnt->getSubEntity(0)->setCustomParameter(1, Ogre::Vector4(0.0, 0.0, 1.0, 1.0));
	//_SinbadEnt->setMaterialName("shader/custom");

	Ogre::Light* light = _sceneManager->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1, -1, 0));
	_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	//_sceneManager->setAmbientLight(Ogre::ColourValue(.3f,.3f,.3f));

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
