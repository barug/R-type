

#include "PhysicSystem.hpp"
#include "GuiSystem.hpp"

const std::string PhysicSystem::name = "PhysicSystem";

PhysicSystem::PhysicSystem(EntityManager &entityManager,
			   MessageBus &messageBus,
			   unsigned int winX,
			   unsigned int winY)
  : ASystem(entityManager, messageBus),
    _winX(winX),
    _winY(winY)
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
  if (!(!physComp->getCanLeaveScreen() && (newPosX < 0 || newPosX > (int) (_winX) ||
					   newPosY < 0 || newPosY > (int) (_winY))))
    {
      posComp->setX(newPosX);
      posComp->setY(newPosY);
    }
  else
    {
      physComp->setSpeedX(0);
      physComp->setSpeedY(0);
    }
}
