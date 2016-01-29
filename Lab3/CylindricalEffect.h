#pragma once

class CylindricalEffect
{
private:
	Ogre::Entity* _entity;
	Ogre::Vector3 _position;
	Ogre::Vector3 _velocity;

public:
	CylindricalEffect(Ogre::Entity* entity, Ogre::Vector3 position, Ogre::Vector3 velocity);
	~CylindricalEffect();
	Ogre::Vector3 getCartesian();
	void update(float dt);
};
