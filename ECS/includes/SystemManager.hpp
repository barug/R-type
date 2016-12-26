//
// SystemManager.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Tue Dec 13 13:15:36 2016 Thomas Billot
// Last update Thu Dec 22 01:05:34 2016 Thomas Billot
//

#pragma once

# include		<memory>
# include		<map>
# include		"ASystem.hpp"
# include		"EntityManager.hpp"

class			EntityManager;

class			SystemManager
{

  EntityManager		&_entityManager;
  MessageBus		&_messageBus;
  std::map<std::string, std::shared_ptr<ASystem> >	_systems;
  
public:

  SystemManager(EntityManager &entityManager, MessageBus &messageBus);
  ~SystemManager();

  bool			addSystem(std::shared_ptr<ASystem> systemToAdd,
				  std::string name,
				  std::vector<std::string> affectedComponents,
				  std::vector<int> suscribedToMessages);
  bool			removeSystem(const std::string &systemToRemove);
  void		        debugSystem();
  void		        updateSystems();
  
private:

  SystemManager(const SystemManager &);
  SystemManager		&operator=(const SystemManager &);
  
};
