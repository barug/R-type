

#include "PhysicSystem.hpp"

PhysicSystem::PhysicSystem(EntityManager &entityManager, MessageBus &messageBus)
  : ASystem(entityManager, messageBus)
{}

void		PhysicSystem::updateEntity(int entityId)
{
  PositionComponent *posComp =
    static_cast<PositionComponent*>(_entityManager.getComponent(entityId,
								"PositionComponent"));
  PhysicComponent *physComp =
    static_cast<PhysicComponent*>(_entityManager.getComponent(entityId,
							      "PhysicComponent"));

  physComp->setSpeedX(physComp->getSpeedX() + physComp->getAccelerationX());
  physComp->setSpeedY(physComp->getSpeedY() + physComp->getAccelerationY());
  posComp->setX(posComp->getX() + physComp->getSpeedX());
  posComp->setY(posComp->getY() + physComp->getSpeedY());
}
