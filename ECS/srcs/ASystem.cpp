#include <iostream>
#include "ASystem.hpp"

ASystem::ASystem(EntityManager &entityManager, MessageBus &messageBus)
  : _entityManager(entityManager),
    _messageBus(messageBus),
    _affectedEntities()
{
  loadMessageHandler(MessageBus::ENTITY_CREATED, &ASystem::handleEntityCreated);
  loadMessageHandler(MessageBus::ENTITY_DESTROYED, &ASystem::handleEntityDeleted);
}

void			ASystem::addName(const std::string &name)
{
  _name = name;
}

void			ASystem::addAffectedComponents(const std::vector<std::string> &affectedComponents)
{
  for(std::string affectedComponent: affectedComponents)
    {
      _mask |= _entityManager.getComponentMask(affectedComponent);
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
  auto			it = _messageHandlers.find(messageTypeId);

  if (it != _messageHandlers.end())
    {
      (this->*_messageHandlers[messageTypeId])(messageData);
      return;
    }
  throw std::runtime_error("No function for this message");
}


void			ASystem::update()
{
  preRoutine();
  for (std::vector<int>::const_iterator it = _affectedEntities.begin();
       it != _affectedEntities.end();
       ++it)
    {
      updateEntity(*it);
    }
  postRoutine();
}

void			ASystem::handleEntityCreated(void *messageData)
{
  int			*entity = static_cast<int*>(messageData);

  if ((_entityManager.getEntityType(*entity) & _mask) == _mask)
  _affectedEntities.push_back(*entity);
}

void			ASystem::handleEntityDeleted(void *messageData)
{
  int			*entity = static_cast<int*>(messageData);

  for (auto it = _affectedEntities.begin();
       it != _affectedEntities.end();
       ++it)
    if (*it == *entity)
      {
	_affectedEntities.erase(it);
	return;
      }
}
