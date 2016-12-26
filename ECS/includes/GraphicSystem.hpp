//
// GraphicSystem.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Tue Dec 13 14:21:56 2016 Thomas Billot
// Last update Thu Dec 22 01:19:47 2016 Thomas Billot
//

#pragma once

#include <string>
#include "ASystem.hpp"
#include "MessageBus.hpp"

class			GraphicSystem : public ASystem
{

public:

  GraphicSystem();
  virtual ~GraphicSystem();

  virtual void update();
};

extern "C"
{
  
  ASystem* createGraphicSystem();
}
