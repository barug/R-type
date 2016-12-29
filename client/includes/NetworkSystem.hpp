#ifndef         __NETWORK_SYSTEM_HPP__
# define        __NETWORK_SYSTEM_HPP__

# include       "ASystem.hpp"
# include       "RTypeClient.hpp"
# include       "EntityManager.hpp"
# include       "MessageBus.hpp"

class           NetworkSystem : public ASystem
{

public:

  enum		Messages
    {
      AUTHENTIFICATION_FAILED = 13,
    }; 
  
  static const std::string	name;
  
  NetworkSystem(EntityManager &entityManager, MessageBus &messageBus);
  virtual ~NetworkSystem();
  virtual void  preRoutine(void);
  virtual void  postRoutine(void);
  virtual void  updateEntity(int entityId);

  void		handleAuthentification(void *MessageData);
  
private:
  
  RTypeClient   *_client;
  bool		_isAuthentified;
};

#endif          // !__NETWORK_SYSTEM_HPP__
