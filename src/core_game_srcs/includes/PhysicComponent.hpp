
#ifndef _PHYSIC_COMPONENT_HPP_
# define _PHYSIC_COMPONENT_HPP_

#include "IComponent.hpp"

class			PhysicComponent : public IComponent
{
  int			_speedX;
  int			_speedY;
  int			_accelerationX;
  int			_accelerationY;

public:
  PhysicComponent();
  virtual const std::string name();
  void			setSpeedX(int speedX);
  void			setSpeedY(int speedY);
  void			setAccelerationX(int accelerationX);
  void			setAccelerationY(int accelerationY);
  int			getSpeedX() const;
  int			getSpeedY() const;
  int			getAccelerationX() const;
  int			getAccelerationY() const;
};

#endif /* !_PHYSIC_COMPONENT_HPP_ */
