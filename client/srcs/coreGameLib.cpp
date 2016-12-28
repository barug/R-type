
#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "PositionComponent.hpp"
#include "PhysicComponent.hpp"
#include "PhysicSystem.hpp"
#include "GuiSystem.hpp"
#include "SpriteComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "PlayerInputSystem.hpp"

void	loadGameLibData(EntityManager &e, SystemManager &s, MessageBus &m)
{
  e.addComponentType<PositionComponent>("PositionComponent");
  e.addComponentType<PhysicComponent>("PhysicComponent");
  e.addComponentType<PlayerInputComponent>("PlayerInputComponent");
  e.addComponentType<SpriteComponent>("SpriteComponent");
  s.addSystem(std::make_shared<GuiSystem>(e, m),
	      "GuiSystem",
	      {"SpriteComponent", "PositionComponent"},
	      {});
  s.addSystem(std::make_shared<PhysicSystem>(e, m),
	      "PhysicSystem",
	      {"PhysicComponent", "PositionComponent"},
	      {});
  s.addSystem(std::make_shared<PlayerInputSystem>(e, m),
  	      "PlayerInputSystem",
  	      {"PhysicComponent", "PlayerInputComponent"},
  	      {});
  e.addEntityType("PlayerShip",
		  e.getComponentMask("PositionComponent")
		  | e.getComponentMask("PhysicComponent")
		  | e.getComponentMask("PlayerInputComponent")
		  | e.getComponentMask("SpriteComponent"));
}

typedef void (*loaderPtr)(EntityManager &, SystemManager &, MessageBus &);

extern "C" loaderPtr returnLoader()
{
  return loadGameLibData;
}
