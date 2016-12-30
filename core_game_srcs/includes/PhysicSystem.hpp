
#ifndef _PHYSIC_SYSTEM_HPP_
# define _PHYSIC_SYSTEM_HPP_

# include "ASystem.hpp"
# include "PositionComponent.hpp"
# include "PhysicComponent.hpp"

class				PhysicSystem : public ASystem
{
  unsigned int			_winX;
  unsigned int			_winY;
  
public:

  static const std::string	name;
  
  PhysicSystem(EntityManager &entityManager,
	       MessageBus &messageBus,
	       unsigned int winX,
	       unsigned int winY);
  virtual void			preRoutine() {};
  virtual void			updateEntity(int entityId);
  virtual void			postRoutine() {};
};

#endif /* !_PHYSIC_SYSTEM_HPP_ */
