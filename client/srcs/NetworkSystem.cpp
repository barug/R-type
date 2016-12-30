# include	<iostream>
# include       "NetworkSystem.hpp"
# include	"GuiSystem.hpp"

const std::string NetworkSystem::name = "NetworkSystem";

NetworkSystem::NetworkSystem(EntityManager &entityManager, MessageBus &messageBus)
  : ASystem(entityManager, messageBus),
    _client(new RTypeClient()),
    _isAuthentified(false)
{
  loadMessageHandler(GuiSystem::Messages::AUTHENTIFICATION,
		     static_cast<message_handler>(&NetworkSystem::handleAuthentification));
}

NetworkSystem::~NetworkSystem()
{}

void            NetworkSystem::preRoutine(void)
{}

void            NetworkSystem::updateEntity(int entityId)
{
  static int	ticks = 0;

  if (_isAuthentified)
    {
      if (_client->run() != true)
	{
	  std::cout << "RTypeClient::run return false" << std::endl;
	  std::cout << "This " << ticks++ << " tick auth is still not done" << std::endl;
	  if (ticks >= 100)
	    {
	      _isAuthentified = false;
	      _messageBus.post(Messages::AUTHENTIFICATION_FAILED, NULL);
	      ticks = 0;
	    }
	  ticks++;
	}
      else
      	_messageBus.post(Messages::AUTHENTIFICATION_SUCCESS, NULL);
    }
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
