
#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "PhysicComponent.hpp"
#include "PhysicSystem.hpp"

typedef void (*loaderPtr)(EntityManager &, SystemManager &, MessageBus &);

void	loadGameLibData(EntityManager &e, SystemManager &s, MessageBus &m);

extern "C"
{
  loaderPtr returnLoader();
}
