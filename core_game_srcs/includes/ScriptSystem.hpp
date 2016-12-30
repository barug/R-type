
#ifndef _SCRIPT_SYSTEM_HPP_
# define _SCRIPT_SYSTEM_HPP_

# include "ASystem.hpp"
# include "ScriptComponent.hpp"

class			ScriptSystem : public ASystem
{
public:

  static const std::string	name;

  ScriptSystem(EntityManager &entityManager, MessageBus &messageBus);

  virtual void			preRoutine() {};
  virtual void			updateEntity(int entityId);
  virtual void			postRoutine() {};
};


#endif /* !_SCRIPT_SYSTEM_HPP_ */
