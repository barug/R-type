//
// PhysicComponent.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Nov 29 10:28:14 2016 Thomas Billot
// Last update Tue Nov 29 14:19:35 2016 Thomas Billot
//

#ifndef		_PHYSICCOMPONENT_HPP_
# define	_PHYSICCOMPONENT_HPP_

# include	"IComponent.hpp"

class		PhysicComponent : public IComponent
{

  int		_x;
  int		_y;
  
public:

  explicit PhysicComponent(int x = 0, int y = 0) : _x(x),
					  _y(y)
  {}
  virtual	~PhysicComponent() {}
  virtual void	debug();
  int		getX() const {return _x;}
  int		getY() const {return _y;}
};

std::ostream	&operator<<(std::ostream &os, const PhysicComponent &obj);

#endif		/* _PHYSICCOMPONENT_HPP_ */
