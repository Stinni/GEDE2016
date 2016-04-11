#pragma once
#include "stdafx.h"

#include "OGRE/OgreSceneNode.h"
#include "LinearMath\btMotionState.h"

class OgreMotionState : public btMotionState {
public:
	OgreMotionState(const btTransform &initialpos, Ogre::SceneNode *node) {
		mVisibleobj = node;
		mPos1 = initialpos;
	}
 
	virtual ~OgreMotionState() {
	}
 
	void setNode(Ogre::SceneNode *node) {
		mVisibleobj = node;
	}
 
	virtual void getWorldTransform(btTransform &worldTrans) const {
		worldTrans = mPos1;
	}
 
	virtual void setWorldTransform(const btTransform &worldTrans) {
		if (NULL == mVisibleobj)
			return;
		btQuaternion rot = worldTrans.getRotation();
		mVisibleobj->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
		btVector3 pos = worldTrans.getOrigin();
		mVisibleobj->setPosition(pos.x(), pos.y(), pos.z());
	}
 
protected:
	Ogre::SceneNode *mVisibleobj;
	btTransform mPos1;
};