
#ifndef _PHYSIC_COMPOENT_HPP_
# define _PHYSIC_COMPOENT_HPP_

class			PhysicComponent : public IComponent
{
  int			_speedX;
  int			_speedY;
  int			_accelerationX;
  int			_accelerationY;

public:
  PhysicComponent(int speed, int mass, int acceleration);
  void			setSpeedX(int speedX);
  void			setSpeedY(int speedY);
  void			setAccelerationX(int accelerationX);
  void			setAccelerationY(int accelerationY);
  int			getSpeedX() const;
  int			getSpeedY() const;
  int			getAccelerationX() const;
  int			getAccelerationY() const;
}

#endif /* !_PHYSIC_COMPOENT_HPP_ */
