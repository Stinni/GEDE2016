#pragma once
#include "stdafx.h"

#include "Ogre/OgreEntity.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include <vector>
#include <map>
#include "OgreMotionState.h"

class Physics{
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	std::vector<btCollisionShape *> collisionShapes;
	std::map<std::string, btRigidBody *> physicsAccessors;
public:
	Physics();
    void initObjects();
	virtual ~Physics();
	btDiscreteDynamicsWorld* getDynamicsWorld();
	btRigidBody* AddDynamicCubeRigidBody(Ogre::SceneNode* node, Ogre::Entity* ent, btScalar mass);
};
