//
// EntityManager.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Fri Nov 25 16:51:37 2016 Thomas Billot
// Last update Tue Dec 27 10:33:44 2016 Thomas Billot
//

#ifndef					_ENTITYMANAGER_HPP_
# define				_ENTITYMANAGER_HPP_

# include				<array>
# include				<map>
# include				<vector>
# include				<memory>
# include				<type_traits>
# include				<stdexcept>
# include				"IComponent.hpp"
# include				"MessageBus.hpp"

class MessageBus;

class					EntityManager
{ 

public:  

  typedef enum
    {
      NONE = 0,
      USED = 1
    }					eState;
  
  const static int			_maxEntities = 500;

  typedef std::array<std::unique_ptr<IComponent>, _maxEntities> component_pool;
  
  EntityManager(MessageBus &messageBus);
  ~EntityManager();

  template<typename ComponentType>
  void					addComponentType(std::string name)
  {
    if (!std::is_base_of<IComponent, ComponentType>::value)
      throw std::logic_error("Component is not derived from IComponent");
    
    auto componentPool = std::make_shared<component_pool>();
    for (auto it = componentPool->begin();
	 it != componentPool->end();
	 ++it)
      {
	*it = std::unique_ptr<IComponent>(new ComponentType);
      }
    _components[name] = componentPool;
  }
  
  int					createComponentMask(const std::string &name);
  int					getComponentMask(const std::string &name);
  IComponent				*getComponent(int entityId,
						      const std::string &componentType);
  
  void					addEntityType(const std::string &typeName,
						      int mask);
  int					createEntity(const std::string &typeName);
  void					deleteEntity(int id);

  std::shared_ptr<std::vector<IComponent*> > getComponentsById(int entity) const;
  std::shared_ptr<component_pool>	getArrayByName(const std::string &name);
  const std::array<int, EntityManager::_maxEntities> &getEntities() const;

  MessageBus				&getMessageBus();
  
private:
  
  MessageBus				&_messageBus;
  std::array<int, _maxEntities>		_entities;
  std::array<int, _maxEntities>		_typeOfEntities;
  std::map<std::string, int>		_entityTypes;
  std::map<std::string, int>		_componentMasks;
  std::map<std::string, std::shared_ptr<component_pool> >  _components;
};

#endif					/* _ENTITYMANAGER_HPP_ */