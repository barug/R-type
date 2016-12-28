
#ifndef _PLAYER_INPUT_COMPONENT_HPP_
# define _PLAYER_INPUT_COMPONENT_HPP_

#include "IComponent.hpp"

class			PlayerInputComponent : public IComponent
{
public:

  static const std::string	name;
  
  PlayerInputComponent();
  virtual const std::string		getName();
};

#endif /* !_PLAYER_INPUT_COMPONENT_HPP_ */
