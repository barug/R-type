//
// PhysicSystem.cpp for  in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec 13 13:07:06 2016 Thomas Billot
// Last update Tue Dec 27 10:12:54 2016 Thomas Billot
//

#pragma once

# include "ASystem.hpp"

class			PhysicSystem : public ASystem
{

public:
  
  PhysicSystem();
  virtual ~PhysicSystem();

  virtual void		updateEntity(int entityId);
};
