
#ifndef _POSITION_COMPONENT_HPP_
# define _POSITION_COMPONENT_HPP_

# include "IComponent.hpp"

class				PositionComponent : public IComponent
{
  int				_x;
  int				_y;

public:

  static const std::string	name;
  
  PositionComponent();
  virtual const std::string	getName();
  void				setX(int x);
  void				setY(int y);
  int				getX() const;
  int				getY() const;
};

#endif /* _POSITION_COMPONENT_HPP_ */
