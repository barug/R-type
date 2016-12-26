//
// GraphicComponent.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Nov 29 13:25:12 2016 Thomas Billot
// Last update Tue Nov 29 14:21:08 2016 Thomas Billot
//

#ifndef			_GRAPHICCOMPONENT_HPP_
# define		_GRAPHICCOMPONENT_HPP_

# include		"IComponent.hpp"
# include		<string>

class			GraphicComponent : public IComponent
{

  std::string		_path;
  
public:

  GraphicComponent(const std::string &path) : _path() {}
  virtual		~GraphicComponent() {}
  virtual void		debug() {std::cout << _path << std::endl;}
  const std::string	&getPath() const {return _path;}
  
};

#endif			/* _GRAPHICCOMPONENT_HPP_ */
