//
// GraphicSystem.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Tue Dec 13 14:21:56 2016 Thomas Billot
// Last update Tue Dec 27 10:13:13 2016 Thomas Billot
//

#pragma once

#include "ASystem.hpp"

class			GraphicSystem : public ASystem
{

public:

  GraphicSystem();
  virtual ~GraphicSystem();

  virtual void updateEntity(int entityId);
};
