# include       "NetworkSystem.hpp"

NetworkSystem::NetworkSystem(EntityManager &entityManager, MessageBus &messageBus)
  : ASystem(entityManager, messageBus),
    _client(new RTypeClient())
{}

NetworkSystem::~NetworkSystem()
{}

void            NetworkSystem::preRoutine(void)
{}

void            NetworkSystem::updateEntity(int entityId)
{}

void            NetworkSystem::postRoutine(void)
{}
