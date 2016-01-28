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
	float oldX = _position.x;
	float y = _position.y;
	float oldZ = _position.z;
	float radius = sqrt(oldX*oldX+oldZ*oldZ);
	float alpha = Ogre::Math::ATan(oldZ/oldX);
	// Ogre::Math::Cos()
	// Ogre::Math::Sin()
	//X coordinate = cosine of the angle times the radius
	float newX = Ogre::Math::Cos(alpha) * radius;
	//Z Coordinate = sin(angle) times the radius
	float newZ = Ogre::Math::Sin(alpha) * radius;
	return Ogre::Vector3(newX, y, newZ);
	Ogre::Math::DegreesToRadians();
}

void CylindricalEffect::update(float dt) {
    _position = _position + dt*_velocity;
    _entity->getParentSceneNode()->setPosition(getCartesian());	
}
