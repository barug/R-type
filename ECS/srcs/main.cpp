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
#if defined(__UNIX__)
	  GameEngine		g("./gameLibs/");
	  g.run();
#elif defined(WIN32) || defined(_WIN32)
	  GameEngine		g("./gameLibs/Release/");
	  g.run();
#endif
  }
  catch (const std::exception &e)
    {
      std::cout << e.what() << std::endl;
    }
  return 0;
}
