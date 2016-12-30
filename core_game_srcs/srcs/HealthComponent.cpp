
#include "HealthComponent.hpp"

const std::string	HealthComponent::name = "HealthComponent";

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

void			HealthComponent::modifyHealth(int modifier)
{
  _health += modifier;
}

void			HealthComponent::setFaction(HealthComponent::Faction faction)
{
  _faction = faction;
}

HealthComponent::Faction	HealthComponent::getFaction() const
{
  return _faction;
}

void			HealthComponent::setDamagePower(int damagePower)
{
  _damagePower = damagePower;
}

int			HealthComponent::getDamagePower() const
{
  return _damagePower;
}
