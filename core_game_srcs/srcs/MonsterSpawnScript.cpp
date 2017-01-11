
#include "MonsterSpawnScript.hpp"
#include "BasicMonsterScript.hpp"

MonsterSpawnScript::MonsterSpawnScript(EntityManager &entityManager)
  : _entityManager(entityManager),
    _lastSpawn(std::chrono::system_clock::now()),
    _rd(),
    _mt(_rd()),
    _yValueDistribution(200, 600),
    _monsterTypeDistribution(1, 2)
{

}


void		MonsterSpawnScript::operator()()
{
  std::chrono::time_point<std::chrono::system_clock> now =
    std::chrono::system_clock::now();
  if (std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastSpawn).count()
      > 3000)
      {
	_lastSpawn = now;
	int yValue = _yValueDistribution(_mt);
	int monsterType = _monsterTypeDistribution(_mt);
	_entityManager.createEntity("BasicMonster",
				    1199,
				    yValue,
				    -2);

	// switch (monsterType)
	//   {
	//   case 1:
	//     _entityManager.createEntity("BasicMonster",
	// 				1199,
	// 				yValue,
	// 				-2,
	// 				0);
	//     break;
	//   case 2:
	//     _entityManager.createEntity("BasicMonster", 1199, yValue, -2, 0);
	//     break;
	//   }
      }
}
