#pragma once

# include "IComponent.hpp"

class					NetworkComponent : public IComponent
{

  std::string				_ip;
  int					_port;

public:

  static const std::string		name;
  virtual const std::string		getName();
  explicit				NetworkComponent();
  virtual				~NetworkComponent();
};
