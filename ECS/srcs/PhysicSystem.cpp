//
// PhysicSystem.cpp for  in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec 13 13:07:06 2016 Thomas Billot
// Last update Tue Dec 27 10:11:25 2016 Thomas Billot
//

#include	<iostream>
#include	"Systems.hpp"
#include	"Components.hpp"

PhysicSystem::PhysicSystem()
  : ASystem()
{
}

PhysicSystem::~PhysicSystem() {}

void				PhysicSystem::updateEntity(int entityId)
{
  std::cout << "Called update on PhysicSystem with entityId= " << entityId << std::endl;
  PositionComponent *posComponent = static_cast<PositionComponent*>(_entityManager->getComponent(entityId, "PositionComponent"));
  if (posComponent)
    {
  std::cout << posComponent->_x << " " << posComponent->_y << std::endl;
    }
}
