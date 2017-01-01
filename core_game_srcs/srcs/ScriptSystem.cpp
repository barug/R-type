
#include "ScriptSystem.hpp"

const std::string	ScriptSystem::name = "ScriptSystem";
  
ScriptSystem::ScriptSystem(EntityManager &entityManager, MessageBus &messageBus)
  : ASystem(entityManager, messageBus)
{
  _entityManager.createEntity("MonsterSpawnScript");
}

void			ScriptSystem::updateEntity(int entityId)
{
  ScriptComponent *scriptComp =
    static_cast<ScriptComponent*>(_entityManager.getComponent(entityId,
							        ScriptComponent::name));
  scriptComp->executeScript();
}
