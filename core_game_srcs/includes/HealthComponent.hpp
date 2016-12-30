
#ifndef _HEALTH_COMPONENT_HPP_
# define _HEALTH_COMPONENT_HPP_

# include "IComponent.hpp"

class				HealthComponent : public IComponent
{
public:
  enum				Faction
    {
      PLAYERS,
      ENEMIES
    };

private:
  int				_health;
  int				_damagePower;
  HealthComponent::Faction	_faction;
  
public:
  static const std::string	name;

  HealthComponent();
  virtual const std::string	getName();
  void				setHealth(int health);
  int				getHealth() const;
  void				modifyHealth(int modifier);
  void				setFaction(HealthComponent::Faction faction);
  HealthComponent::Faction	getFaction() const;
  void				setDamagePower(int damagePower);
  int				getDamagePower() const;
};


# endif /* !_HEALTH_COMPONENT_HPP_ */
