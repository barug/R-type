//
// GameEngine.cpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Fri Nov 25 17:20:05 2016 Thomas Billot
// Last update Tue Dec 27 18:27:07 2016 Thomas Billot
//

#include <iostream>
#include <chrono>
#if defined(__GNUC__)
#include <dirent.h>
#elif defined(_WIN32)
#endif
#include "GameEngine.hpp"
#include "PhysicComponent.hpp"
#include "GraphicComponent.hpp"
#include "Systems.hpp"

GameEngine::GameEngine(const std::string &libsDir)
  : _messageBus(),
    _entityManager(_messageBus),
    _systemManager(_entityManager, _messageBus)
{
# if		defined(_WIN32) || defined(WIN32)
  std::unique_ptr<IDynamicLoader> libLoader(new windowsDynamicLoader);
#elif defined(__GNUC__)
  std::unique_ptr<IDynamicLoader> libLoader(new unixDynamicLoader);
#endif

  _libLoader = std::move(libLoader);
  if (!libsDir.empty())
    {
      DIR	*dir;
      struct dirent *ent;
      
      if ((dir = opendir(libsDir.c_str())) != NULL)
	{
	  while ((ent = readdir (dir)) != NULL)
	    {
	      std::string s(libsDir.c_str());

	      s += ent->d_name;
	      loadLib(s);
	    }
	  closedir (dir);
	}
    }
}

void			GameEngine::loadLib(const std::string &libPath)
{
  std::size_t found = libPath.find_last_of(".");
  if (libPath.substr(found + 1) == "so")
    {
      int (*fPtr)(EntityManager &, SystemManager &) = _libLoader->load(libPath, "returnLoader");

      fPtr(_entityManager, _systemManager);
    }
}

GameEngine::~GameEngine()
{}

int			GameEngine::run(void)
{
  std::shared_ptr<ASystem>	sysPhysic = std::make_shared<PhysicSystem>();
  std::shared_ptr<ASystem>	sysGraphic = std::make_shared<GraphicSystem>();
  std::shared_ptr<ASystem>	sysInput = std::make_shared<InputSystem>();
  
  _systemManager.addSystem(sysPhysic, "PhysicSystem", { "MassComponent", "PositionComponent" }, {});
  _systemManager.addSystem(sysGraphic, "GraphicSystem", { "MeshComponent" }, {});
  _systemManager.addSystem(sysInput, "InputSystem", {"PositionComponent"}, {});
  _entityManager.createEntity("MyMonster");
  /*		       ^
  ** REMOVE THIS AFTER | RESERVED FOR UNIT TESTS
  */
  
  bool			run = true;
  std::chrono::time_point<std::chrono::system_clock> now, then;
  then = std::chrono::system_clock::now();
  
  while (run)
    {
      now = std::chrono::system_clock::now();
      int elapsed =
	std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count();
      if (elapsed >= 10)
	{
	  _systemManager.updateSystems();
	  _messageBus.broadcast();
	  then = now;
	}
    }
  return 0;
}
