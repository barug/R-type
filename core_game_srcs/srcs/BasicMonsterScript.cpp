
#include "BasicMonsterScript.hpp"
#include "PhysicComponent.hpp"

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
      _ySpeedModifier = - _ySpeedModifier;
      _lastSwitch = now;
    }
  physComp->modifySpeedY(_ySpeedModifier);
}
