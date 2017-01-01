
#include "MonsterSpawnScript.hpp"

MonsterSpawnScript::MonsterSpawnScript(EntityManager &entityManager)
  : _entityManager(entityManager),
    _lastSpawn(std::chrono::system_clock::now())
{

}


void		MonsterSpawnScript::operator()()
{
  std::chrono::time_point<std::chrono::system_clock> now =
    std::chrono::system_clock::now();
  if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastSpawn).count()
      > 1000)
      {
	_lastSpawn = now;
	_entityManager.createEntity("BasicMonster", 1199, 400, -2);
      }
}
