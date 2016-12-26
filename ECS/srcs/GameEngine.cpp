//
// GameEngine.cpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
//
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
//
// Started on  Fri Nov 25 17:20:05 2016 Thomas Billot
// Last update Thu Dec 22 20:58:27 2016 Thomas Billot
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
#include "PhysicSystem.hpp"
#include "GraphicSystem.hpp"
#include "IDynamicLoader.hpp"
#include "IMonster.hpp"

GameEngine::GameEngine(std::string libsDir)
  : _messageBus(),
    _entityManager(_messageBus),
    _systemManager(_entityManager, _messageBus)
{
  //if (!libsDir.empty())
  //  {
  //     DIR	*dir;
  //     struct dirent *ent;
  //     
  //     if ((dir = opendir(libsDir.c_str())) != NULL)
  //{
	//  while ((ent = readdir (dir)) != NULL)
	//    {
	//      loadLib(ent->d_name);
	//    }
	//  closedir (dir);
	//}
    //}
}

void			GameEngine::loadLib(std::string libPath)
{
  
}

GameEngine::~GameEngine()
{}

//std::vector<IComponent*>	createPlayer()
//{}

int			GameEngine::run(void)
{
  // std::unique_ptr<IDynamicLoader<ASystem> > _systemLoader(new unixDynamicLoader<ASystem>);
  // std::unique_ptr<IDynamicLoader<IMonster> > _monsterLoader(new unixDynamicLoader<IMonster>);

# if		defined(_WIN32) || defined(WIN32)
	std::unique_ptr<IDynamicLoader> _libLoader(new windowsDynamicLoader);
#elif defined(__GNUC__)
	std::unique_ptr<IDynamicLoader> _libLoader(new unixDynamicLoader);
#endif
	int(*fptr)(EntityManager &, SystemManager &) = _libLoader->load("./dynamicLibs/lib-MyMonster", "returnLoader");

	fptr(_entityManager, _systemManager);
	std::shared_ptr<ASystem>	sysPhysic = std::make_shared<PhysicSystem>();
	std::shared_ptr<ASystem>	sysGraphic = std::make_shared<GraphicSystem>();
	_systemManager.addSystem(sysPhysic, "PhysicSystem", { "placeholder" }, { 1, 2, 4 });
	_systemManager.addSystem(sysGraphic, "GraphicSystem", { "placeholder" }, { 1 });

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
