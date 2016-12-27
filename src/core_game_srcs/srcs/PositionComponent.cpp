
#include "PositionComponent.hpp"

PositionComponent::PositionComponent(int x, int y)
  : _x(x),
    _y(y)
{}

virtual const std::string	PositionComponent::name()
{
  return "PositionComponent"
}

void				PositionComponent::setX(int x)
{
  _x = x;
}

void				PositionComponent::setY(int y)
{
  _y = y;
}

int				PositionComponent::getX() const
{
  return _x;
}

int				PositionComponent::getY() const
{
  return _y;
}
