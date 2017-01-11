
#include "strafingMonsterScript.hpp"

StrafingMonsterScript::StrafingMonsterScript(EntityManager &entityManager,
					     int entityId)
  : _entityManager(entityManager),
    _entityId(entityId),
    _startChrono(std::chrono::system_clock::now()),
    _lastSwitch(std::chrono::system_clock::now()),
    _lastFire(std::chrono::system_clock::now())
{}

void			StrafingMonsterScript::operator()()
{
  PhysicComponent *physComp =
    static_cast<PhysicComponent*>(_entityManager.getComponent(_entityId,
							      PhysicComponent::name));
  std::chrono::time_point<std::chrono::system_clock> now =
    std::chrono::system_clock::now();
  if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _startChrono).count()
      > 1000)
    {
      physComp->setSpeedX(0);
      if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastSwitch).count()
	  > 2000)
	{
	  if (physComp->getSpeedY() == 0)
	    {
	      physComp->setSpeedY(2);
	    }
	  physComp->setSpeedY(- physComp->getSpeedY());
	  _lastSwitch = now;
	}
      if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastFire).count()
	  > 1000)
	{
	  PositionComponent *posComp =
	    static_cast<PositionComponent*>(_entityManager.getComponent(_entityId,
									PositionComponent::name));      
	  _entityManager.createEntity("basicProjectile",
				      posComp->getX() - 20,
				      posComp->getY(),
				      -10,
				      std::vector<unsigned int>({208/12,
					    0,
					    208/12,
					    18}).data(),
				      12,
				      HealthComponent::Faction::ENEMIES,
				      "./assets/sprites/r-typesheet3.png");
	  _lastFire = now;
	}
    }
}
