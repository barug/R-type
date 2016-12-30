
#include "HitBoxComponent.hpp"

const std::string	HitBoxComponent::name = "HitBoxComponent.hpp";

HitBoxComponent::HitBoxComponent()
{}

const std::string HitBoxComponent::getName()
{
  return HitBoxComponent::name;
}
  
void			HitBoxComponent::setCircleRadius(int circleRadius)
{
  _circleRadius = circleRadius;
}

const int		HitBoxComponent::getCircleRadius() const
{
  return _circleRadius;
}

