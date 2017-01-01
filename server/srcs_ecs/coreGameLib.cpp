#include <iostream>
#include "../../ECS/includes/SystemManager.hpp"
#include "../../ECS/includes/EntityManager.hpp"
#include "../../core_game_srcs/includes/PositionComponent.hpp"
#include "../../core_game_srcs/includes/PhysicComponent.hpp"
#include "../../core_game_srcs/includes/PhysicSystem.hpp"
#include "../includes_ecs/NetworkSystem.hpp"
#include "../includes_ecs/NetworkComponent.hpp"
#include "../../core_game_srcs/includes/HitBoxComponent.hpp"
#include "../../core_game_srcs/includes/CollisionSystem.hpp"
#include "../../core_game_srcs/includes/HealthComponent.hpp"
#include "../../core_game_srcs/includes/HealthSystem.hpp"
#include "../includes_ecs/serverMessages.hpp"
#include "../../core_game_srcs/includes/ScriptComponent.hpp"
#include "../../core_game_srcs/includes/ScriptSystem.hpp"

void	loadGameLibData(EntityManager &e, SystemManager &s, MessageBus &m)
{
  unsigned int		winX = 1200;
  unsigned int		winY = 800;

  std::cout << "[loading game data]" << std::endl;
  e.addComponentType<PositionComponent>(PositionComponent::name);
  e.addComponentType<PhysicComponent>(PhysicComponent::name);
  e.addComponentType<HitBoxComponent>(HitBoxComponent::name);
  e.addComponentType<HealthComponent>(HealthComponent::name);
  e.addComponentType<ScriptComponent>(ScriptComponent::name);
  e.addComponentType<NetworkComponent>(NetworkComponent::name);
  m.registerValidMessageId(CoreGameSrcsMessages::COLLISION_DETECTED);
  m.registerValidMessageId(ServerMessages::ADD_CLIENT);
  m.registerValidMessageId(ServerMessages::SOCKET_ROOM);
  e.addEntityType("PlayerShip",
		  {PositionComponent::name,
		      PhysicComponent::name,
		      PlayerInputComponent::name,
		      SpriteComponent::name,
		      HitBoxComponent::name,
		      HealthComponent::name},
		  initializePlayerShip);
  e.addEntityType("BasicMonster",
		  {PositionComponent::name,
		      PhysicComponent::name,
		      SpriteComponent::name,
		      HitBoxComponent::name,
		      HealthComponent::name,
		      ScriptComponent::name},
		  initializeBasicMonster);
  e.addEntityType("playerBasicProjectile",
		  {PositionComponent::name,
		      PhysicComponent::name,
		      SpriteComponent::name,
		      HitBoxComponent::name,
		      HealthComponent::name},
		  initializePlayerBasicProjectile);
  s.addSystem(std::make_shared<PhysicSystem>(e, m, winX, winY),
  	      PhysicSystem::name,
  	      {PhysicComponent::name,
  		  PositionComponent::name},
  	      {});
  std::cout << "Before Network" << std::endl;
  s.addSystem(std::make_shared<NetworkSystem>(e, m),
  	      NetworkSystem::name,
  	      {NetworkComponent::name},
  	      {ServerMessages::ADD_CLIENT,
		  ServerMessages::SOCKET_ROOM});
  std::cout << "After Network" << std::endl;
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
  e.createEntity("PlayerShip");
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
