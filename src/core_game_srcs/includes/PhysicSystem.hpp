
#ifndef _POSITION_COMPONENT_HPP_
# define _POSITION_COMPONENT_HPP_

# include "PositionComponent.hpp"
# include "PhysicComponent.hpp"

class			PhysicSystem : public ASystem
{
public:
  PhysicSystem();
  virtual void		preRoutine() {};
  virtual void		updateEntity(int entityId);
  virtual void		postRoutine() {};
}

#endif /* !_POSITION_COMPONENT_HPP_ */
