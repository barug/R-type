#ifndef         __NETWORK_SYSTEM_HPP__
# define        __NETWORK_SYSTEM_HPP__

# include       "ASystem.hpp"
# include       "RTypeClient.hpp"
# include       "EntityManager.hpp"
# include       "MessageBus.hpp"
# include	"serverMessages.hpp"

class           NetworkSystem : public ASystem
{

public:
  
  static const std::string	name;
  
  NetworkSystem(EntityManager &entityManager, MessageBus &messageBus);
  virtual ~NetworkSystem();
  virtual void  preRoutine(void);
  virtual void  postRoutine(void);
  virtual void  updateEntity(int entityId);

  void		handleAddClient(void *MessageData);
  
private:
  
  std::vector<std::pair<std::string, int>>   _clients;
  bool					     _hasGameStarted;
};

#endif          // !__NETWORK_SYSTEM_HPP__
