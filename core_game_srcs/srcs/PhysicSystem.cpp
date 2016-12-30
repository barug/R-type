

#include "PhysicSystem.hpp"

const std::string PhysicSystem::name = "PhysicSystem";

PhysicSystem::PhysicSystem(EntityManager &entityManager, MessageBus &messageBus)
  : ASystem(entityManager, messageBus)
{}

void		PhysicSystem::updateEntity(int entityId)
{
  int		newPosX;
  int		newPosY;
  PositionComponent *posComp =
    static_cast<PositionComponent*>(_entityManager.getComponent(entityId,
								"PositionComponent"));
  PhysicComponent *physComp =
    static_cast<PhysicComponent*>(_entityManager.getComponent(entityId,
							      "PhysicComponent"));

  newPosX = posComp->getX() + physComp->getSpeedX();
  newPosY = posComp->getY() + physComp->getSpeedY();
  // physComp->setSpeedX(physComp->getSpeedX() + physComp->getAccelerationX());
  // physComp->setSpeedY(physComp->getSpeedY() + physComp->getAccelerationY());
  // if (!(!physComp->getCanLeaveScreen && (newPosX < 0 || newPosX
  posComp->setX(newPosX);
  posComp->setY(newPosY);
}
