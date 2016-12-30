
#include "BasicMonsterScript.hpp"

BasicMonsterScript::BasicMonsterScript(EntityManager &entityManager, int entityId)
  : _entityManager(entityManager),
    _entityId(entityId),
    _ySpeedModifier(1),
    _lastSwitch(std::chrono::system_clock::now())
{}

BasicMonsterScript::~BasicMonsterScript()
{}

void		BasicMonsterScript::operator()()
{
  std::chrono::time_point<std::chrono::system_clock> now =
    std::chrono::system_clock::now();
  if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastSwitch).count()
      > 500)
    {
      _ySpeedModifier = - _ySpeedModifier;
      _lastSwitch = now;
    }
}
