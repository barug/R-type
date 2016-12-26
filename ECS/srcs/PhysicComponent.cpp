//
// PhysicComponent.cpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Nov 29 13:35:07 2016 Thomas Billot
// Last update Tue Nov 29 14:20:13 2016 Thomas Billot
//

#include <iostream>
#include "PhysicComponent.hpp"

void			PhysicComponent::debug()
{
  std::cout << _x << " " << _y << std::endl;
}

std::ostream		&operator<<(std::ostream &os, const PhysicComponent &obj)
{
  return (os << "PhysicComponent " << &obj << ": x=" << obj.getX() << " y=" << obj.getY());
}
