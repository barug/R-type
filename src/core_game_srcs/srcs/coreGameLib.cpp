
#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "PositionComponent.hpp"
#include "PhysicComponent.hpp"
#include "PhysicSystem.hpp"
#include "GuiSystem.hpp"

void	loadGameLibData(EntityManager &e, SystemManager &s, MessageBus &m)
{
  e.addComponentType<PositionComponent>("PositionComponent");
  e.addComponentType<PhysicComponent>("PhysicComponent");
  s.addSystem(std::make_shared<GuiSystem>(e, m),
	      "GuiSystem",
	      {"SpriteComponent", "PositionComponent"},
	      {});
  s.addSystem(std::make_shared<PhysicSystem>(e, m),
	      "PhysicSystem",
	      {"PhysicComponent", "PositionComponent"},
	      {});
}

typedef void (*loaderPtr)(EntityManager &, SystemManager &, MessageBus &);

extern "C" loaderPtr returnLoader()
{
  return loadGameLibData;
}
