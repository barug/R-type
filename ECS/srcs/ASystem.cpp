
#include "ASystem.hpp"

ASystem::ASystem()
{}

void			ASystem::addEntityManager(EntityManager *entityManager)
{
  _entityManager = entityManager;
}

void			ASystem::addMessageBus(MessageBus *messageBus)
{
  _messageBus = messageBus;
}

void			ASystem::addName(std::string &name)
{
  _name = name;
}

void			ASystem::addAffectedComponents(std::vector<std::string> &affectedComponents)
{
  for(std::string affectedComponent: affectedComponents)
    {
      _mask |= _entityManager->getComponentMask(affectedComponent);
    }
}							


const std::string	&ASystem::name() const
{
  return _name;
}

void			ASystem::loadMessageHandler(int messageTypeId,
						    message_handler handler)
{
  _messageHandlers[messageTypeId] = handler;
}

void			ASystem::handleMessage(int messageTypeId,
					       void *messageData)
{
  (this->*_messageHandlers[messageTypeId])(messageData);
}

void			ASystem::handleEntityCreated(void *messageData)
{
  int			*((int*)messageData);
  
  _entit
}
