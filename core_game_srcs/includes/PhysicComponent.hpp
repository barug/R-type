
#ifndef _PHYSIC_COMPONENT_HPP_
# define _PHYSIC_COMPONENT_HPP_

#include "IComponent.hpp"

class				PhysicComponent : public IComponent
{
  float				_speedX;
  float				_speedY;
  float				_accelerationX;
  float				_accelerationY;
  bool				_canLeaveScreen;
  
public:

  static const std::string	name;
  
  PhysicComponent();
  virtual const std::string getName();
  void				setSpeedX(float speedX);
  void				setSpeedY(float speedY);
  void				modifySpeedX(float modifier);
  void				modifySpeedY(float modifier);
  void				setAccelerationX(float accelerationX);
  void				setAccelerationY(float accelerationY);
  void				setCanLeaveScreen(bool canLeaveScreen);
  float				getSpeedX() const;
  float				getSpeedY() const;
  float				getAccelerationX() const;
  float				getAccelerationY() const;
  bool				getCanLeaveScreen() const;
  
};

#endif /* !_PHYSIC_COMPONENT_HPP_ */
