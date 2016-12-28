#ifndef         __NETWORK_SYSTEM_HPP__
# define        __NETWORK_SYSTEM_HPP__

# include       "ASystem.hpp"
# include       "RTypeClient.hpp"
# include       "EntityManager.hpp"
# include       "MessageBus.hpp"

class           NetworkSystem : public ASystem
{
 public:
  NetworkSystem(EntityManager &entityManager, MessageBus &messageBus);
  virtual ~NetworkSystem();
  virtual void  preRoutine(void);
  virtual void  postRoutine(void);
  virtual void  updateEntity(int entityId);

private:
  RTypeClient   *client;
};

#endif          // !__NETWORK_SYSTEM_HPP__
