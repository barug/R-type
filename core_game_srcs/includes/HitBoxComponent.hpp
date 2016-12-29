
#ifndef _HITBOX_COMPONENT_HPP
# define _HITBOX_COMPONENT_HPP

# include "IComponent.hpp"

class			HitBoxComponent : public IComponent
{
  int			_circleRadius;
public:

  static const std::string	name;
  
  HitBoxComponent();
  virtual const std::string getName();
  void			setCircleRadius(int circleRadius);
  const int		getCircleRadius() const;
};

#endif /* !_HITBOX_COMPONENT_HPP */
