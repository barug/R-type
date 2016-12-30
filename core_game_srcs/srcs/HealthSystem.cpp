
#include "HealthSystem.hpp"
#include "CollisionSystem.hpp"
#include <iostream>
const std::string		HealthSystem::name = "HealthSystem";

HealthSystem::HealthSystem(EntityManager &entityManager, MessageBus &messageBus)
  : ASystem(entityManager, messageBus)
{
  loadMessageHandler(CollisionSystem::Messages::COLLISION_DETECTED,
  		     static_cast<message_handler>(&HealthSystem::handleCollision));
}

void				HealthSystem::updateEntity(int entityId)
{
  HealthComponent		*healthComp =
    static_cast<HealthComponent*>(_entityManager.getComponent(entityId,
  							      HealthComponent::name));

  if (healthComp->getHealth() <= 0)
    {
      std::cout << "deleting entity" << std::endl;
      _entityManager.deleteEntity(entityId);
    }
}

void				HealthSystem::handleCollision(void *messageData)
{
  std::cout << "entering handle collision" << std::endl;
  std::pair<int, int>		*idPair =
    static_cast<std::pair<int, int>*>(messageData);
  std::cout << "firstId: " << idPair->first << std::endl;
  std::cout << "secondId: " << idPair->second << std::endl;
  HealthComponent		*firstHealthComp =
    static_cast<HealthComponent*>(_entityManager.getComponent(idPair->first,
							       HealthComponent::name));
  HealthComponent		*secondHealthComp =
    static_cast<HealthComponent*>(_entityManager.getComponent(idPair->second,
							      HealthComponent::name));
  std::cout << "firstHealthCompPtr: " << firstHealthComp << std::endl;
  std::cout << "secondHealthCompPtr: " << secondHealthComp << std::endl;
  if (firstHealthComp && secondHealthComp &&
      firstHealthComp->getFaction() != secondHealthComp->getFaction())
    {
      firstHealthComp->modifyHealth(secondHealthComp->getDamagePower());
      secondHealthComp->modifyHealth(firstHealthComp->getDamagePower());
      // if (firstHealthComp->getHealth() <= 0)
      // 	{
      // 	  std::cout << "deleting entity" << std::endl;
      // 	  _entityManager.deleteEntity(idPair->first);
      // 	}
      // if (secondHealthComp->getHealth() <= 0)
      // 	{
      // 	  std::cout << "deleting entity" << std::endl;
      // 	  _entityManager.deleteEntity(idPair->second);
      // 	}
    }
}
