
#include "BasicMonsterScript.hpp"
#include "PhysicComponent.hpp"
#include "PositionComponent.hpp"
#include "HealthComponent.hpp"

BasicMonsterScript::BasicMonsterScript(EntityManager &entityManager, int entityId)
  : _entityManager(entityManager),
    _entityId(entityId),
    _ySpeedModifier(0.1),
    _lastSwitch(std::chrono::system_clock::now())
{}

BasicMonsterScript::~BasicMonsterScript()
{}

void		BasicMonsterScript::operator()()
{
  PhysicComponent *physComp =
    static_cast<PhysicComponent*>(_entityManager.getComponent(_entityId,
							      PhysicComponent::name));
  std::chrono::time_point<std::chrono::system_clock> now =
    std::chrono::system_clock::now();
  if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastSwitch).count()
      > 1000)
    {
      PositionComponent *posComp =
	static_cast<PositionComponent*>(_entityManager.getComponent(_entityId,
								  PositionComponent::name));      
      _ySpeedModifier = - _ySpeedModifier;
      _lastSwitch = now;
      _entityManager.createEntity("basicProjectile",
				  posComp->getX() - 20,
				  posComp->getY(),
				  -10,
				  0,
				  std::vector<unsigned int>({208/12,
					0,
					208/12,
					18}).data(),
				  12,
				  HealthComponent::Faction::ENEMIES,
				  "./assets/sprites/r-typesheet3.png");
	}
  physComp->modifySpeedY(_ySpeedModifier);
}
