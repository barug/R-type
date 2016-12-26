//
// SystemManager.cpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec 13 13:18:17 2016 Thomas Billot
// Last update Thu Dec 22 01:07:54 2016 Thomas Billot
//

#include	<iostream>
#include	<memory>
#include	"SystemManager.hpp"

SystemManager::SystemManager(EntityManager &entityManager, MessageBus &messageBus)
  :_entityManager(entityManager),
   _messageBus(messageBus),
   _systems() {}

SystemManager::~SystemManager() {}

bool		SystemManager::addSystem(std::shared_ptr<ASystem> systemToAdd,
					 std::string name,
					 std::vector<std::string> affectedComponents,
					 std::vector<int> suscribedToMessages)
{
  if (systemToAdd && !name.empty() && !affectedComponents.empty())
    {
      systemToAdd->addEntityManager(&_entityManager);
      systemToAdd->addName(name);
      systemToAdd->addAffectedComponents(affectedComponents);
      systemToAdd->addMessageBus(&_messageBus);
      _messageBus.registerSystem(systemToAdd);
      // for (int messageId: MessagesSuscribedTo)
      // 	{
      // 	  _messageBus.subscribeToMessage(name, messageId);
      // 	}
      _systems.emplace(systemToAdd->name(), std::move(systemToAdd));
      return true;
    }
  throw std::logic_error("addSystem failed !");
}

bool		SystemManager::removeSystem(const std::string &systemToRemove)
{
  auto found = _systems.find(systemToRemove);

  if (found != _systems.end())
    {
      _systems.erase(found);
      return true;
    }
  throw std::logic_error("removeSystem failed");
}

void		SystemManager::updateSystems()
{
  for (std::map<std::string, std::shared_ptr<ASystem> >::const_iterator it = _systems.begin();
       it != _systems.end();
       ++it)
    {
      it->second->update();
    }
}

void		SystemManager::debugSystem()
{
  for (std::map<std::string, std::shared_ptr<ASystem> >::const_iterator it = _systems.begin();
       it != _systems.end();
       ++it)
    {
      //std::cout << it->second->name() << std::endl;
    }
}
