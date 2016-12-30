

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

bool		PhysicSystem::testIfOutScreen(int x, int y)
{
  return (x < 0 || x > (int) (_winX) ||
	  y < 0 || y > (int) (_winY));
}

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
  if (physComp->getCanLeaveScreen())
    {
      if (!testIfOutScreen(newPosX, newPosY))
	{
	  posComp->setX(newPosX);
	  posComp->setY(newPosY);
	}
      else
	{
	  _entityManager.deleteEntity(entityId);
	}
      
    }
  else
    {
      if (!testIfOutScreen(newPosX, newPosY))
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
}
