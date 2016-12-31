#include <iostream>
#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "PositionComponent.hpp"
#include "PhysicComponent.hpp"
#include "PhysicSystem.hpp"
#include "GuiSystem.hpp"
#include "SpriteComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "PlayerInputSystem.hpp"
#include "NetworkSystem.hpp"
#include "HitBoxComponent.hpp"
#include "CollisionSystem.hpp"
#include "HealthComponent.hpp"
#include "HealthSystem.hpp"
#include "clientMessages.hpp"
#include "ScriptComponent.hpp"
#include "ScriptSystem.hpp"

void	loadGameLibData(EntityManager &e, SystemManager &s, MessageBus &m)
{
  unsigned int		winX = 1200;
  unsigned int		winY = 800;

  std::cout << "[loading game data]" << std::endl;
  e.addComponentType<PositionComponent>(PositionComponent::name);
  e.addComponentType<PhysicComponent>(PhysicComponent::name);
  e.addComponentType<PlayerInputComponent>(PlayerInputComponent::name);
  e.addComponentType<SpriteComponent>(SpriteComponent::name);
  e.addComponentType<HitBoxComponent>(HitBoxComponent::name);
  e.addComponentType<HealthComponent>(HealthComponent::name);
  e.addComponentType<ScriptComponent>(ScriptComponent::name);
  m.registerValidMessageId(ClientMessages::KEY_INPUT_DATA);
  m.registerValidMessageId(ClientMessages::AUTHENTIFICATION);
  m.registerValidMessageId(ClientMessages::AUTHENTIFICATION_FAILED);
  m.registerValidMessageId(ClientMessages::AUTHENTIFICATION_SUCCESS);
  m.registerValidMessageId(CoreGameSrcsMessages::COLLISION_DETECTED);
  m.registerValidMessageId(CoreGameSrcsMessages::ENTITY_DEATH);
  e.addEntityType("PlayerShip",
		  {PositionComponent::name,
		      PhysicComponent::name,
		      PlayerInputComponent::name,
		      SpriteComponent::name,
		      HitBoxComponent::name,
		      HealthComponent::name});
  e.addEntityType("BasicMonster",
		  {PositionComponent::name,
		      PhysicComponent::name,
		      SpriteComponent::name,
		      HitBoxComponent::name,
		      HealthComponent::name,
		      ScriptComponent::name});
  e.addEntityType("playerBasicProjectile",
		  {PositionComponent::name,
		      PhysicComponent::name,
		      SpriteComponent::name,
		      HitBoxComponent::name,
		      HealthComponent::name});
  s.addSystem(std::make_shared<GuiSystem>(e, m, winX, winY),
	      GuiSystem::name,
	      {SpriteComponent::name,
		  PositionComponent::name},
	      {ClientMessages::AUTHENTIFICATION_FAILED,
		  ClientMessages::AUTHENTIFICATION_SUCCESS,
		  // CoreGameSrcsMessages::ENTITY_DEATH
		  });
  s.addSystem(std::make_shared<PhysicSystem>(e, m, winX, winY),
	      PhysicSystem::name,
	      {PhysicComponent::name,
		  PositionComponent::name},
	      {});
  s.addSystem(std::make_shared<PlayerInputSystem>(e, m),
  	      PlayerInputSystem::name,
  	      {PhysicComponent::name,
		  PlayerInputComponent::name,
		  PositionComponent::name},
  	      {ClientMessages::KEY_INPUT_DATA});
  s.addSystem(std::make_shared<NetworkSystem>(e, m),
  	      NetworkSystem::name,
  	      {PhysicComponent::name},
  	      {ClientMessages::AUTHENTIFICATION,
		  ClientMessages::KEY_INPUT_DATA});
  s.addSystem(std::make_shared<CollisionSystem>(e, m),
	      CollisionSystem::name,
	      {PositionComponent::name,
		  HitBoxComponent::name},
	      {});
  s.addSystem(std::make_shared<HealthSystem>(e, m),
  	      HealthSystem::name,
  	      {HealthComponent::name},
  	      {CoreGameSrcsMessages::COLLISION_DETECTED});
  s.addSystem(std::make_shared<ScriptSystem>(e, m),
  	      ScriptSystem::name,
  	      {ScriptComponent::name},
  	      {});
  std::cout << "DONE LOADING" << std::endl;
}

#if defined(__GNUC__)
typedef void(*loaderPtr)(EntityManager &, SystemManager &, MessageBus &);
extern "C" loaderPtr returnLoader()
{
	return &loadGameLibData;
}
#elif defined(_WIN32) || defined(WIN32)
#ifdef BUILD_DLL
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

typedef void(*loaderPtr)(EntityManager &, SystemManager &, MessageBus &);
__declspec(dllexport) extern "C" {
	loaderPtr returnLoader()
	{
		return &loadGameLibData;
	}
}

#endif
