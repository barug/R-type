
#include "PhysicComponent.hpp"

PhysicComponent::PhysicComponent()
{}

const std::string	PhysicComponent::name()
{
  return "PhysicComponent";
}

void			PhysicComponent::setSpeedX(int speedX)
{
  _speedX = speedX;
}

void			PhysicComponent::setSpeedY(int speedY)
{
  _speedY = speedY;
}

void			PhysicComponent::setAccelerationX(int accelerationX)
{
  _accelerationX = accelerationX;
}

void			PhysicComponent::setAccelerationY(int accelerationY)
{
  _accelerationY = accelerationY;
}

int			PhysicComponent::getSpeedX() const
{
  return _speedX;
}

int			PhysicComponent::getSpeedY() const
{
  return _speedY;
}

int			PhysicComponent::getAccelerationX() const
{
  return _accelerationX;
}

int			PhysicComponent::getAccelerationY() const
{
  return _accelerationY;
}
