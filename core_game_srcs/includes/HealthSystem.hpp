
#ifndef _HEALTH_SYSTEM_HPP_
# define _HEALTH_SYSTEM_HPP_

#include "ASystem.hpp"
#include "HealthComponent.hpp"

class			HealthSystem : public ASystem
{

public:

  static const std::string	name;

  HealthSystem(EntityManager &entityManager, MessageBus &messageBus);
  virtual void			preRoutine() {}
  virtual void			updateEntity(int entityId);
  virtual void			postRoutine() {}

  void				handleCollision(void *messageData);
};

#endif /* !_HEALTH_SYSTEM_HPP_ */
