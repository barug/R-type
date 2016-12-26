//
// GraphicSystem.cpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Tue Dec 13 14:40:43 2016 Thomas Billot
// Last update Thu Dec 22 18:30:06 2016 Thomas Billot
//

#include	<iostream>
#include	"GraphicSystem.hpp"

GraphicSystem::GraphicSystem()
  : ASystem()
{
  // std::shared_ptr<MessageBus> tmp(&bus);

  // _messageBus = tmp;
}

GraphicSystem::~GraphicSystem() {}

void		GraphicSystem::update()
{
  _messageBus->post(2, NULL);
}
