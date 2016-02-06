#include "MyApplication.h"

MyApplication::MyApplication()
{
	_sceneManager = NULL;
	_root = NULL;
	_listener = NULL;
	_ceffect = NULL;
}
MyApplication::~MyApplication()
{
	delete _root;
	delete _listener;
	delete _ceffect;
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

	Ogre::RenderWindow* window = _root->initialise(true, "Ogre3D Beginners Guide - Lab4");

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
	_listener = new MyFrameListener(window, camera, _SinbadNode, _SinbadEnt, _ceffect);
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
	_myCube = _sceneManager->createEntity("Cube.mesh");
	cubenode = _SinbadEnt->getParentSceneNode()->createChildSceneNode();
	cubenode->attachObject(_myCube);
	
	_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ground);
	ground->setMaterialName("Examples/BeachStones");
	
	cubenode->scale(0.01f, 0.01f, 0.01f);
	cubenode->setPosition(5.0f, 2.5f, 0.0f);

	//Ogre::Entity* myModel = _sceneManager->createEntity("Ceramic_Cup", "Ceramic_Cup.mesh");
	Ogre::Entity* StarModel1 = _sceneManager->createEntity("My_Crappy_Star1", "My_Crappy_Star/My_Crappy_Star.mesh");
	//Ogre::Entity* StarModel2 = _sceneManager->createEntity("My_Crappy_Star2", "My_Crappy_Star/My_Crappy_Star.mesh");
	//Ogre::Entity* StarModel3 = _sceneManager->createEntity("My_Crappy_Star3", "My_Crappy_Star/My_Crappy_Star.mesh");
	Ogre::Entity* StarModel4 = _sceneManager->createEntity("My_Crappy_Star4", "My_Crappy_Star2/My_Crappy_Star.mesh");
	//StarModel2->setMaterialName("BlueMaterial");
	//StarModel3->setMaterialName("RedMaterial");
	Ogre::SceneNode* starNode1 =_sceneManager->getRootSceneNode()->createChildSceneNode();
	//Ogre::SceneNode* starNode2 =_sceneManager->getRootSceneNode()->createChildSceneNode();
	//Ogre::SceneNode* starNode3 =_sceneManager->getRootSceneNode()->createChildSceneNode();
	Ogre::SceneNode* starNode4 =_sceneManager->getRootSceneNode()->createChildSceneNode();
	starNode1->attachObject(StarModel1);
	//starNode2->attachObject(StarModel2);
	//starNode3->attachObject(StarModel3);
	starNode4->attachObject(StarModel4);
	starNode1->setScale(1.2f, 1.2f, 1.2f);
	//starNode2->setScale(1.2f, 1.2f, 1.2f);
	//starNode3->setScale(1.2f, 1.2f, 1.2f);
	starNode4->setScale(1.2f, 1.2f, 1.2f);
	starNode1->setPosition(10.0f, -1.5f, 10.0f);
	//starNode2->setPosition(-10.0f, -1.5f, -10.0f);
	//starNode3->setPosition(10.0f, -1.5f, -10.0f);
	starNode4->setPosition(-10.0f, -1.5f, 10.0f);

	Ogre::Light* light = _sceneManager->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1, -1, 0));
	_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	//_sceneManager->setAmbientLight(Ogre::ColourValue(.3f,.3f,.3f));

	Ogre::Light* plight = _sceneManager->createLight("Light2");
	plight->setType(Ogre::Light::LT_POINT);
	cubenode->attachObject(plight);

	_ceffect = new CylindricalEffect(_myCube, cubenode->getPosition(),
		Ogre::Vector3(0.0f, 0.0f, 2.5f));
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
