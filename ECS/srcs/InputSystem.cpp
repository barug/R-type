//
// InputSystem.cpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/cpp_rtype/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec 27 16:28:24 2016 Thomas Billot
// Last update Tue Dec 27 19:15:49 2016 Thomas Billot
//

#include		<iostream>
#include		"InputSystem.hpp"

InputSystem::InputSystem() : _keyBindings(),
			     _actionBindings(),
			     _gui()
{}

InputSystem::~InputSystem()
{}

void			InputSystem::assignKey(Action actionToMap, sf::Keyboard::Key keyToMap)
{
  _keyBindings[keyToMap] = actionToMap;
}

sf::Keyboard::Key	InputSystem::getAssignedKey(Action actionToFind)
{
  for (auto it : _keyBindings)
    {
      if (it.second == actionToFind)
	return it.first;
    }
  throw std::logic_error("Error: No action assign to this key");
}

void			InputSystem::updateEntity(int entityId)
{
  std::cout << "yay" << std::endl;
}
