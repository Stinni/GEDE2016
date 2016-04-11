#include "stdafx.h"
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
	#if _DEBUG
		cf.load("../LabFiles/OgreConfig/resources_d.cfg");
	#elif NDEBUG
		cf.load("../LabFiles/OgreConfig/resources.cfg");
	#endif
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
	#if _DEBUG
		_root = new Ogre::Root("../LabFiles/OgreConfig/plugins_d.cfg","../LabFiles/OgreConfig/ogre.cfg", "../LabFiles/ogre.log");
	#elif NDEBUG
		_root = new Ogre::Root("../LabFiles/OgreConfig/plugins.cfg","../LabFiles/OgreConfig/ogre.cfg", "../LabFiles/ogre.log");
	#endif

	if(!_root->showConfigDialog()) {
		return -1;
	}

	Ogre::RenderWindow* window = _root->initialise(true, "Ogre3D Beginners Guide - Lab9");

	_sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);
	Ogre::Camera* camera = _sceneManager->createCamera("Camera");

	camera->setPosition(Ogre::Vector3(0,0,30));
	camera->lookAt(Ogre::Vector3(0,0,0));
	camera->setNearClipDistance(0.5);

	Ogre::Viewport* viewport = window->addViewport(camera);
	viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
	camera->setAspectRatio(Ogre::Real(viewport->getActualWidth())/Ogre::Real(viewport->getActualHeight()));

	loadResources();
	createScene();

	_physicsEngine = new Physics();
	_physicsEngine->initObjects();
	_listener = new MyFrameListener(window, camera, _SinbadNode, _SinbadEnt, _sceneManager, _physicsEngine);
	_root->addFrameListener(_listener);

	return 0;
}

void MyApplication::createScene()
{
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, -1);
	Ogre::MeshManager::getSingleton().createPlane("plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
		1500, 1500, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* ground = _sceneManager->createEntity("LightPlaneEntity", "plane");
	Ogre::SceneNode* _groundNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
	_groundNode->attachObject(ground);
	ground->setMaterialName("Examples/BeachStones");
	_groundNode->setPosition(0, -1, 0);

	// Create the collision shape, and give it the ground plane normals.
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(plane.normal.x, plane.normal.y, plane.normal.z), 0);
 
	// Create the collision transform.
	btTransform groundTransform;
 
	// Set up the collision location and orientation.
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(_groundNode->getPosition().x, _groundNode->getPosition().y, _groundNode->getPosition().z));
	btQuaternion initRotation(_groundNode->getOrientation().x, _groundNode->getOrientation().y, _groundNode->getOrientation().z, _groundNode->getOrientation().w);
	groundTransform.setRotation(initRotation);

	// Give the plane a mass of 0, because our plane will be static, thus will not moce.
	btScalar mass(0.0f);
 
	// Set the ground as a static object.
	bool isDynamic = false;

	// This plane isnt going to be moving so i dont care about setting the motion state
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape);
	btRigidBody* body = new btRigidBody(rbInfo);
 
	//add the body to the dynamics world
	_physicsEngine->getDynamicsWorld()->addRigidBody(body);

	int ringCount = 16;
	int ringheight = 10;
	for (int i = 0; i < ringheight; ++i) {
		for (int j = 0; j < ringCount; ++j) {
			Ogre::Entity* cubeEnt = _sceneManager->createEntity("Cube.mesh");
			Ogre::SceneNode* cubeNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
			cubeNode->setScale(0.006f, 0.004f, 0.006f);
			Ogre::Radian angle((Ogre::Math::TWO_PI / ringCount)*j + (Ogre::Math::TWO_PI / ringCount)*0.5f*(i%2) );
 
			cubeNode->setOrientation(Ogre::Quaternion(-angle, Ogre::Vector3::UNIT_Y));
			//cubeNode->setPosition(j*0.62+((i%2)*0.31f), i*0.405-(1-0.2), 0);
 
			cubeNode->setPosition(Ogre::Math::Cos(angle) * 1.9f, i*0.405f - (1 - 0.2f), Ogre::Math::Sin(angle) * 1.9f);
 
			cubeNode->attachObject(cubeEnt);
			btRigidBody* temp = _physicsEngine->AddDynamicCubeRigidBody(cubeNode, cubeEnt, 1);
			temp->setFriction(1);
		}	
	}

	_SinbadEnt = _sceneManager->createEntity("Sinbad.mesh");
	_SinbadNode = _sceneManager->getRootSceneNode()->createChildSceneNode();
	_SinbadNode->attachObject(_SinbadEnt);
	_SinbadNode->scale(Ogre::Vector3(0.2f,0.2f,0.2f));
	_myCube = _sceneManager->createEntity("Cube.mesh");
	cubenode = _SinbadEnt->getParentSceneNode()->createChildSceneNode();
	cubenode->attachObject(_myCube);

	_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(ground);

	cubenode->scale(0.01f, 0.01f, 0.01f);
	cubenode->setPosition(5.0f, 2.5f, 0.0f);

	Ogre::Light* light = _sceneManager->createLight("Light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1, -1, 0));
	_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	Ogre::Light* plight = _sceneManager->createLight("Light2");
	plight->setType(Ogre::Light::LT_POINT);
	cubenode->attachObject(plight);
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
