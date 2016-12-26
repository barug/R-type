//
// IMonster.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec 13 20:10:40 2016 Thomas Billot
// Last update Tue Dec 13 20:11:47 2016 Thomas Billot
//

#pragma once

#include	"IComponent.hpp"

class		IMonster
{
public:

  virtual ~IMonster() = 0;
  virtual const std::vector<std::unique_ptr<IComponent> > &getComponents() const = 0;
};
