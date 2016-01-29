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
	float x = _position.x * Ogre::Math::Cos(_position.z);
	float y = _position.y;
	float z = _position.x * Ogre::Math::Sin(_position.z);
	return Ogre::Vector3(x, y, z);
}

void CylindricalEffect::update(float dt) {
    _position = _position + dt*_velocity;
    _entity->getParentSceneNode()->setPosition(getCartesian());	
}
