
#ifndef _PLAYER_INPUT_COMPONENT_HPP_
# define _PLAYER_INPUT_COMPONENT_HPP_

#include <chrono>
#include "IComponent.hpp"

class			PlayerInputComponent : public IComponent
{

  std::chrono::time_point<std::chrono::system_clock> _lastFire;  
  
public:

  static const std::string	name;
  
  PlayerInputComponent();
  virtual const std::string		getName();
  const std::chrono::time_point<std::chrono::system_clock>	&getLastFire() const;
  void	setLastFire(const std::chrono::time_point<std::chrono::system_clock> &lastFire);
};

#endif /* !_PLAYER_INPUT_COMPONENT_HPP_ */
