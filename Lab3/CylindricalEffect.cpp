#include "CylindricalEffect.h"


CylindricalEffect::CylindricalEffect(Ogre::Entity* entity, Ogre::Vector3 position, Ogre::Vector3 velocity)
{
	_entity = entity;
	_position = position;
	_velocity = velocity;
}

CylindricalEffect::~CylindricalEffect()
{
}

Ogre::Vector3 CylindricalEffect::getCartesian()
{
	// Ogre::Math::Cos()
	// Ogre::Math::Sin()
	//X coordinate = cosine of the angle times the radius
	float x = 1;
	//Y coordinate = height
	float y = 1;
	//Z Coordinate = sin(angle) times the radius
	float z = 1;
	return Ogre::Vector3(x, y, z);
}

void CylindricalEffect::update(float dt) {
    _position = _position + dt*_velocity;
    _entity->getParentSceneNode()->setPosition(getCartesian());	
}
