
#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "PositionComponent.hpp"
#include "PhysicComponent.hpp"
#include "PhysicSystem.hpp"
#include "GuiSystem.hpp"
#include "SpriteComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "PlayerInputSystem.hpp"
#include "HitBoxComponent.hpp"
#include "CollisionSystem.hpp"

void	loadGameLibData(EntityManager &e, SystemManager &s, MessageBus &m)
{
  e.addComponentType<PositionComponent>(PositionComponent::name);
  e.addComponentType<PhysicComponent>(PhysicComponent::name);
  e.addComponentType<PlayerInputComponent>(PlayerInputComponent::name);
  e.addComponentType<SpriteComponent>(SpriteComponent::name);
  e.addComponentType<HitBoxComponent>(HitBoxComponent::name);
  m.registerValidMessageId(GuiSystem::Messages::KEY_INPUT_DATA);
  e.addEntityType("PlayerShip",
		  {PositionComponent::name,
		      PhysicComponent::name,
		      PlayerInputComponent::name,
		      SpriteComponent::name,
		      HitBoxComponent::name});
  e.addEntityType("BasicMonster",
		  {PositionComponent::name,
		      SpriteComponent::name,
		      HitBoxComponent::name});
  s.addSystem(std::make_shared<GuiSystem>(e, m),
	      GuiSystem::name,
	      {SpriteComponent::name, PositionComponent::name},
	      {});
  s.addSystem(std::make_shared<PhysicSystem>(e, m),
	      PhysicSystem::name,
	      {PhysicComponent::name, PositionComponent::name},
	      {});
  s.addSystem(std::make_shared<PlayerInputSystem>(e, m),
  	      PlayerInputSystem::name,
  	      {PhysicComponent::name, PlayerInputComponent::name},
  	      {GuiSystem::Messages::KEY_INPUT_DATA});
  s.addSystem(std::make_shared<CollisionSystem>(e, m),
	      CollisionSystem::name,
	      {PositionComponent::name, HitBoxComponent::name},
	      {});
}

typedef void (*loaderPtr)(EntityManager &, SystemManager &, MessageBus &);

extern "C" loaderPtr returnLoader()
{
  return loadGameLibData;
}
