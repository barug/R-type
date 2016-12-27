//
// GraphicSystem.cpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Tue Dec 13 14:40:43 2016 Thomas Billot
// Last update Tue Dec 27 10:12:22 2016 Thomas Billot
//

#include	<iostream>
#include	"Systems.hpp"
#include	"Components.hpp"

GraphicSystem::GraphicSystem()
  : ASystem()
{
}

GraphicSystem::~GraphicSystem() {}

void		GraphicSystem::updateEntity(int entityId)
{
  std::cout << "GraphicSystem::updateEntity with id =" << entityId << std::endl; 
}
