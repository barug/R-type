# include	<iostream>
# include       "NetworkSystem.hpp"
# include	"GuiSystem.hpp"

const std::string NetworkSystem::name = "NetworkSystem";

NetworkSystem::NetworkSystem(EntityManager &entityManager, MessageBus &messageBus)
  : ASystem(entityManager, messageBus),
    _client(new RTypeClient()),
    _isAuthentified(false)
{
  loadMessageHandler(ClientMessages::AUTHENTIFICATION,
		     static_cast<message_handler>(&NetworkSystem::handleAuthentification));
}

NetworkSystem::~NetworkSystem()
{}

void            NetworkSystem::preRoutine(void)
{
  static int	ticks = 0;

  if (_isAuthentified)
    {
      if (_client->run() != true)
	{
	  if (ticks >= 100)
	    {
	      _isAuthentified = false;
	      _messageBus.post(ClientMessages::AUTHENTIFICATION_FAILED, NULL);
	      ticks = 0;
	    }
	  ticks++;
	}
      else
      	_messageBus.post(ClientMessages::AUTHENTIFICATION_SUCCESS, NULL);
    }
}

void            NetworkSystem::updateEntity(int entityId)
{
}

void            NetworkSystem::postRoutine(void)
{}

void		NetworkSystem::handleAuthentification(void *messageData)
{
  std::pair<std::string, unsigned int>	*p =
    static_cast<std::pair<std::string, unsigned int>* >(messageData);

  _client->connectToServer(p->first, p->second);
  _isAuthentified = true;
  std::cout << "NetworkSystem::handleAuth" << std::endl;
}
