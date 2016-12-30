
#include "HealthSystem.hpp"
#include <iostream>
const std::string		HealthSystem::name = "HealthSystem";

HealthSystem::HealthSystem(EntityManager &entityManager, MessageBus &messageBus)
  : ASystem(entityManager, messageBus)
{}

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
  std::pair<int, int>		*idPair =
    static_cast<std::pair<int, int>*>(messageData);
  HealthComponent		*firstHealthComp =
    static_cast<HealthComponent*>(_entityManager.getComponent(idPair->first,
							       HealthComponent::name));
  HealthComponent		*secondHealthComp =
    static_cast<HealthComponent*>(_entityManager.getComponent(idPair->second,
							       HealthComponent::name));  
  if (firstHealthComp->getFaction() != secondHealthComp->getFaction())
    {
      firstHealthComp->modifyHealth(secondHealthComp->getDamagePower());
      secondHealthComp->modifyHealth(firstHealthComp->getDamagePower());
    }
}
