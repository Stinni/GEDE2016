#include "OGRE/OgreEntity.h"

class CylindricalEffect
{
private:
	Ogre::Entity* entity;
	Ogre::Vector3 position;
	Ogre::Vector3 velocity;
public:
	CylindricalEffect(Ogre::Entity* entity, Ogre::Vector3 position, Ogre::Vector3 velocity);
	~CylindricalEffect();
};
