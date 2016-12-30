
#ifndef _BASIC_MONSTER_SCRIPT_HPP_
# define _BASIC_MONSTER_SCRIPT_HPP_

# include <chrono>
# include "IScript.hpp"
# include "EntityManager.hpp"

class			BasicMonsterScript : public IScript
{
  EntityManager		&_entityManager;
  int			_entityId;
  int			_ySpeedModifier;
  std::chrono::time_point<std::chrono::system_clock> _lastSwitch;
  
public:
  BasicMonsterScript(EntityManager &entityManager, int entityId);
  virtual ~BasicMonsterScript();
  virtual void		operator()();
};

#endif /* !_BASIC_MONSTER_SCRIPT_HPP_ */
