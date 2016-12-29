
#include <iostream>
#include <cmath>
#include "CollisionSystem.hpp"

const std::string	CollisionSystem::name = "CollisionSystem";

CollisionSystem::CollisionSystem(EntityManager &entityManager,
				 MessageBus &messageBus)
  : ASystem(entityManager, messageBus)
{}

bool		CollisionSystem::testIfAllreadyDetected(int firstId, int secondId)
{
  for (auto idPair: _detectedCollisions)
    {
      if ((idPair.first == firstId && idPair.second == secondId) ||
	  (idPair.first == secondId && idPair.second == firstId))
	return true;
    }
  return false;
}

void CollisionSystem::preRoutine()
{
  _detectedCollisions.clear();
}

void	CollisionSystem::updateEntity(int entityId)
{
  PositionComponent *testedPos =
    static_cast<PositionComponent*>(_entityManager.getComponent(entityId,
								PositionComponent::name));
  HitBoxComponent *testedHitBox =
    static_cast<HitBoxComponent*>(_entityManager.getComponent(entityId,
							      HitBoxComponent::name));
  PositionComponent *otherPos;
  HitBoxComponent *otherHitBox;
  
  for (int otherId: _affectedEntities)
    {
      if (otherId != entityId && !testIfAllreadyDetected(entityId, otherId))
	{
	  
	  otherPos =
	    static_cast<PositionComponent*>(_entityManager.getComponent(otherId,
									PositionComponent::name));
	  otherHitBox =
	    static_cast<HitBoxComponent*>(_entityManager.getComponent(otherId,
								      HitBoxComponent::name));
	  double dx = testedPos->getX() - otherPos->getX();
	  double dy = testedPos->getY() - otherPos->getY();
	  double distance = sqrt(dx * dx + dy * dy);
	  if (distance < testedHitBox->getCircleRadius()
	      + otherHitBox->getCircleRadius())
	    {
	      _detectedCollisions.emplace_back(entityId, otherId);
	    }
	}
    }
}

void CollisionSystem::postRoutine()
{
  for (auto idPair: _detectedCollisions)
    {
      // _messageBus.post(CollisionSystem::detectedCollision,
      // 		       new std::pair(idPair.first,
      // 				     idPair.second));
      std::cout << "detected collision: "
		<< idPair.first  << " and "
		<< idPair.second << std::endl;
    }
}
