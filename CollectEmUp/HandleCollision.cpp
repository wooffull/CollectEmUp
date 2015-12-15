#include "HandleCollision.h"

//void GameObject::handleCollision(GameObject* other )
//{
//	if (other->getSolid())
//	{
//		if (_velocity.y < 0 && _isSolid && _position.y >= other->getPosition().y+other->getBoundingBox()->getHalfWidthY())
//		{
//			_velocity.y = 0;
//			_position.y = other->getPosition().y + other->getBoundingBox()->getHalfWidthY() + _boundingBox->getHalfWidthY();
//		}
//	}
//	else if (other->getGameObjType() == "Collectable" && other->getIsVisible() == true)
//	{
//		other->setIsVisible(false);
//		other->setCollectablesCount(other->getCollectablesCount() += 1);
//	}
//	else
//	{
//		//Add a condition or two and collectable code might go here.
//	}
//}
void handleCollision(GameObject* first, GameObject* other)
{
	if (other->getSolid())
	{
		if (first->getVelocity().y < 0 && first->getSolid() && first->getPosition().y >= other->getPosition().y + other->getBoundingBox()->getHalfWidthY())
		{
			first->setVelocity(vec3(first->getVelocity().x, 0, first->getVelocity().z));
			first->setPosition(vec3(first->getPosition().x, other->getPosition().y + other->getBoundingBox()->getHalfWidthY() + first->getBoundingBox()->getHalfWidthY(), first->getPosition().z));
		}
	}
	else if (dynamic_cast<KeyboardMovableGO*>(first) && dynamic_cast<Collectable*>(other) && other->getIsVisible() == true)
	{
		other->setIsVisible(false);
		auto collectable = dynamic_cast<KeyboardMovableGO*>(first);
		auto collectablesCount = collectable->getCollectablesCount() + 1;
		collectable->setCollectablesCount(collectablesCount);
	}
	else
	{
		//Add a condition or two and collectable code might go here.
	}
}