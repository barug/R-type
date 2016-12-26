//
// ISystem.hpp for ECS in /home/mikaz3/Tek3/B5/AdvancedCpp/ECS
// 
// Made by Thomas Billot
// Login   <mikaz3@epitech.net>
// 
// Started on  Fri Nov 25 14:42:17 2016 Thomas Billot
// Last update Mon Dec 19 15:02:59 2016 Thomas Billot
//

#ifndef			_ASYSTEM_HPP_
# define		_ASYSTEM_HPP_

# include "EntityManager.hpp"
# include "MessageBus.hpp"

class MessageBus;
class EntityManager;

class					ASystem
{

protected:
  typedef void (ASystem::*message_handler)(void *messageData);
  
  int					_mask;
  std::string				_name;
  EntityManager				*_entityManager;
  MessageBus				*_messageBus;
  std::vector<int>			_affectedEntities;
  std::map<int, message_handler>	_messageHandlers;
  
public:

  ASystem();
  virtual		~ASystem() {}

  void			addEntityManager(EntityManager *entityManager);
  void			addMessageBus(MessageBus *messageBus);
  void			addName(std::string &name);
  void			addAffectedComponents(std::vector<std::string> &affectedComponents);
  void			loadMessageHandler(int messageTypeId,
					   message_handler handler);
  void			handleMessage(int messageTypeId,
				      void *messageData);
  void			handleEntityCreated(void *messageData);
  virtual void			update() = 0;
  const std::string	&name() const;
  
};


#endif			/* _ASYSTEM_HPP_ */
