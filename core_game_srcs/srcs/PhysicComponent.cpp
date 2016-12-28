
#include "PhysicComponent.hpp"

const std::string PhysicComponent::name = "PhysicComponent";

PhysicComponent::PhysicComponent()
{}

const std::string	PhysicComponent::getName()
{
  return PhysicComponent::name;
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
