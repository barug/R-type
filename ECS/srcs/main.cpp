//
// main.cpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Fri Nov 25 14:48:49 2016 Thomas Billot
// Last update Tue Dec 27 09:55:18 2016 Thomas Billot
//

#include        <iostream>
#include        "GameEngine.hpp"

int			main()
{
  try
    {
      GameEngine		g("./mods/");
      g.run();
    }
  catch (const std::exception &e)
    {
      std::cout << e.what() << std::endl;
    }
  return 0;
}
