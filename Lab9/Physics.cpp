#include "stdafx.h"
#include "Physics.h"
 
Physics::Physics() { }
 
Physics::~Physics() {
	delete dynamicsWorld;
	delete solver;
	delete overlappingPairCache;
	delete dispatcher;
	delete collisionConfiguration;
}
 
void Physics::initObjects() {
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
}
 
btDiscreteDynamicsWorld* Physics::getDynamicsWorld() {
	return dynamicsWorld;
}

btRigidBody* Physics::AddDynamicCubeRigidBody(Ogre::SceneNode* node, Ogre::Entity* ent, btScalar mass) {
	Ogre::Vector3 aabbSize = ent->getBoundingBox().getSize() / 1.02f;
 
	btScalar x = 0.5f * node->getScale().x * aabbSize.x;
	btScalar y = 0.5f * node->getScale().y * aabbSize.y;
	btScalar z = 0.5f * node->getScale().z * aabbSize.z;
	btCollisionShape* colShape = new btBoxShape(btVector3(x, y, z));
 
	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();
 
	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);
 
	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		colShape->calculateLocalInertia(mass, localInertia);
 
	startTransform.setOrigin(btVector3(node->getPosition().x, node->getPosition().y, node->getPosition().z));
 
	btQuaternion initRotation(node->getOrientation().x, node->getOrientation().y, node->getOrientation().z, node->getOrientation().w);
	startTransform.setRotation(initRotation);
 
	OgreMotionState* motionState = new OgreMotionState(startTransform, node);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, colShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);
 
	dynamicsWorld->addRigidBody(body);
 
	return body;
}