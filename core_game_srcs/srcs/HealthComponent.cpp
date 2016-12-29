
#include "HealthComponent.hpp"

HealthComponent::HealthComponent()
{}

const std::string	HealthComponent::getName()
{
  return HealthComponent::name;
}

void			HealthComponent::setHealth(int health)
{
  _health = health;
}

int			HealthComponent::getHealth() const
{
  return _health;
}
