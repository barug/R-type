
#ifndef _MONSTER_SPAWN_SCRIPT_HPP_
# define _MONSTER_SPAWN_SCRIPT_HPP_
 
# include <chrono>
# include <random>
# include "IScript.hpp"
# include "EntityManager.hpp"

class			MonsterSpawnScript : public IScript
{
  EntityManager		&_entityManager;
  std::chrono::time_point<std::chrono::system_clock> _lastSpawn;
  std::random_device	_rd;
  std::mt19937		_mt;
  std::uniform_int_distribution<int> _yValueDistribution;
  std::uniform_int_distribution<int> _monsterTypeDistribution;

public:
  MonsterSpawnScript(EntityManager &entityManager);
  virtual void		operator()();
};

#endif /* !_MONSTER_SPAWN_SCRIPT_HPP_ */
