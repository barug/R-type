
#ifndef _MONSTER_SPAWN_SCRIPT_HPP_
# define _MONSTER_SPAWN_SCRIPT_HPP_

#include <chrono>
#include "IScript.hpp"
#include "EntityManager.hpp"

class			MonsterSpawnScript : public IScript
{
  EntityManager		&_entityManager;
  std::chrono::time_point<std::chrono::system_clock> _lastSpawn;

public:
  MonsterSpawnScript(EntityManager &entityManager);
  virtual void		operator()();
};

#endif /* !_MONSTER_SPAWN_SCRIPT_HPP_ */
