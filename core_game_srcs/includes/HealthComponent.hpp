
#ifndef _HEALTH_COMPONENT_HPP_
# define _HEALTH_COMPONENT_HPP_

# include "IComponent.hpp"

class				HealthComponent : public IComponent
{

  int				_health;
  
public:
  static const std::string	name;

  HealthComponent();
  virtual const std::string	getName();
  void				setHealth(int health);
  int				getHealth() const;
};


# endif /* !_HEALTH_COMPONENT_HPP_ */
