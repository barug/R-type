
#include "PhysicComponent.hpp"

const std::string PhysicComponent::name = "PhysicComponent";

PhysicComponent::PhysicComponent()
{}

const std::string	PhysicComponent::getName()
{
  return PhysicComponent::name;
}

void			PhysicComponent::setSpeedX(float speedX)
{
  _speedX = speedX;
}

void			PhysicComponent::setSpeedY(float speedY)
{
  _speedY = speedY;
}

void			PhysicComponent::setAccelerationX(float accelerationX)
{
  _accelerationX = accelerationX;
}

void			PhysicComponent::setAccelerationY(float accelerationY)
{
  _accelerationY = accelerationY;
}

void			PhysicComponent::setCanLeaveScreen(bool canLeaveScreen)
{
  _canLeaveScreen = canLeaveScreen;
}


float			PhysicComponent::getSpeedX() const
{
  return _speedX;
}

float			PhysicComponent::getSpeedY() const
{
  return _speedY;
}

float			PhysicComponent::getAccelerationX() const
{
  return _accelerationX;
}

float			PhysicComponent::getAccelerationY() const
{
  return _accelerationY;
}

bool			PhysicComponent::getCanLeaveScreen() const
{
  return _canLeaveScreen;
}
