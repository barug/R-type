
#ifndef _STRAFING_MONSTER_SCRIPT_HPP
# define _STRAFING_MONSTER_SCRIPT_HPP

# include <chrono>
# include "PhysicComponent.hpp"
# include "PositionComponent.hpp"
# include "HealthComponent.hpp"
# include "IScript.hpp"
# include "EntityManager.hpp"

class				StrafingMonsterScript : public IScript
{
  EntityManager			&_entityManager;
  int				_entityId;
  std::chrono::time_point<std::chrono::system_clock> _startChrono;
  std::chrono::time_point<std::chrono::system_clock> _lastSwitch;
  std::chrono::time_point<std::chrono::system_clock> _lastFire;

public:
  StrafingMonsterScript(EntityManager &entityManager, int entityId);
  virtual void			operator()();
};

#endif /* !_STRAFING_MONSTER_SCRIPT_HPP */
