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

	Ogre::RenderWindow* window = _root->initialise(true, "Ogre3D Beginners Guide - Lab2");

	_sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);
	Ogre::Camera* camera = _sceneManager->createCamera("Camera");

	camera->setPosition(Ogre::Vector3(0,0,30));
	camera->lookAt(Ogre::Vector3(0,0,0));
	camera->setNearClipDistance(5);

	Ogre::Viewport* viewport = window->addViewport(camera);
	viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
	camera->setAspectRatio(Ogre::Real(viewport->getActualWidth())/Ogre::Real(viewport->getActualHeight()));

	_listener = new MyFrameListener(window);
	loadResources();
	createScene();
	_root->addFrameListener(_listener);
	_root->startRendering();
	return 0;
}

void MyApplication::createScene()
{
	Ogre::Entity* ent = _sceneManager->createEntity("Sinbad.mesh");
	_sceneManager->getRootSceneNode()->attachObject(ent);
	_sceneManager->setAmbientLight(Ogre::ColourValue(.3f,.3f,.3f));
}
