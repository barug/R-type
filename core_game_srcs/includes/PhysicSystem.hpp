
#ifndef _PHYSIC_SYSTEM_HPP_
# define _PHYSIC_SYSTEM_HPP_

# include "ASystem.hpp"
# include "PositionComponent.hpp"
# include "PhysicComponent.hpp"

class				PhysicSystem : public ASystem
{
public:

  static const std::string	name;
  
  PhysicSystem(EntityManager &entityManager, MessageBus &messageBus);
  virtual void			preRoutine() {};
  virtual void			updateEntity(int entityId);
  virtual void			postRoutine() {};
};

#endif /* !_PHYSIC_SYSTEM_HPP_ */
