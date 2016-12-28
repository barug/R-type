//
// EntityManager.cpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Fri Nov 25 17:06:52 2016 Thomas Billot
// Last update Wed Dec 28 20:01:02 2016 Thomas Billot
//

#include <iostream>
#include <type_traits>
#include <stdexcept>
#include "EntityManager.hpp"

EntityManager::EntityManager(MessageBus &messageBus)
  : _messageBus(messageBus),
    _entities(),
    _componentMasks(),
    _components()
{
  for (unsigned int id = 0; id < EntityManager::_maxEntities; id++)
    _entities[id] = eState::NONE;
}

EntityManager::~EntityManager()
{
  std::cout << "really destroying entity Manager!!!!!!!!" << std::endl;
}

void		EntityManager::addEntityType(const std::string &typeName, const std::vector<std::string> &components)
{
  int		mask = 0;
  
  for (auto it : components)
    {
      mask |= getComponentMask(it);
    }
  _entityTypes[typeName] = mask;
}

int				EntityManager::createEntity(const std::string &typeName)
{
  int typeMask = _entityTypes.at(typeName);
  
  for (unsigned int id = 0; id < EntityManager::_maxEntities; id++)
    {
      if (_entities[id] == eState::NONE)
	{
	  _entities[id] = eState::USED;
	  _typeOfEntities[id] = typeMask;
	  _messageBus.post(MessageBus::ENTITY_CREATED, new int(id));
	  return id;
	}
    }
  return (NONE);
}

void				EntityManager::deleteEntity(int id)
{
  _entities[id] = eState::NONE;
  _messageBus.post(MessageBus::ENTITY_DESTROYED, new int(id));
}

int				EntityManager::createComponentMask(const std::string &name)
{
  static int i = 0;

  _componentMasks.emplace(name, 1 << i++);
  return 1 << i;
}

int				EntityManager::getComponentMask(const std::string &name)
{
  auto it = _componentMasks.find(name);

  if (it != _componentMasks.end())
    return it->second;
  return -1;
}

IComponent			*EntityManager::getComponent(int id,
							    const std::string &componentType)
{
  return (_components[componentType]->at(id)).get();
}

std::shared_ptr<EntityManager::component_pool> EntityManager::getArrayByName(const std::string &name)
{
  std::map<std::string, std::shared_ptr<component_pool >>::const_iterator it = _components.find(name);

  if (it != _components.end())
    {
      return it->second;
    }
  return NULL;
}

//const std::array<int, EntityManager::_maxEntities>	&EntityManager::getEntities() const
//{
//}

std::shared_ptr<std::vector<IComponent*>> EntityManager::getComponentsById(int entity) const
{
  // std::shared_ptr<std::vector<IComponent*> > pV(new std::vector<IComponent*>);
  
  // for (unsigned int id = 0; id < EntityManager::_maxEntities; id++)
  //   {
  //     if (_entities[id] == eSystem::USED)
  // 	{
	  
  // 	  std::pair<std::multimap<int, std::unique_ptr<IComponent>>::const_iterator,
  // 		    std::multimap<int, std::unique_ptr<IComponent>>::const_iterator> ret;
  // 	  ret = _map.equal_range(id);
  // 	  for (std::multimap<int, std::unique_ptr<IComponent> >::const_iterator it = ret.first;
  // 	       it != ret.second;
  // 	       ++it)
  // 	    {
  // 	      pV->push_back(&(*it->second));
  // 	    }
  // 	}
  //   }
  // return pV;
  (void)entity;
  return NULL;
}
