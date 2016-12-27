
#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "PositionComponent.hpp"
#include "PhysicComponent.hpp"
#include "PhysicSystem.hpp"
#include "GuiSystem.hpp"

void	loadGameLibData(EntityManager &e, SystemManager &s)
{
  e.addComponentType<PositionComponent>("PositionComponent");
  e.addComponentType<PhysicComponent>("PhysicComponent");
  s.addSystem(std::make_shared<GuiSystem>(),
	      "GuiSystem",
	      {"SpriteComponent", "PositionComponent"},
	      {});
  s.addSystem(std::make_shared<PhysicSystem>(),
	      "PhysicSystem",
	      {"PhysicComponent", "PositionComponent"},
	      {});
}

typedef void (*loaderPtr)(EntityManager &e, SystemManager &s);

extern "C"
{
  loaderPtr returnLoader()
  {
    return loadGameLibData;
  }
}
