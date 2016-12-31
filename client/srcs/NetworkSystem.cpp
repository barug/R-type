# include	<iostream>
# include       "../includes/NetworkSystem.hpp"
# include	"GuiSystem.hpp"
# include	"clientMessages.hpp"

const std::string NetworkSystem::name = "NetworkSystem";

NetworkSystem::NetworkSystem(EntityManager &entityManager, MessageBus &messageBus)
  : ASystem(entityManager, messageBus),
    _client(new RTypeClient()),
    _isAuthentified(false)
{
  loadMessageHandler(ClientMessages::AUTHENTIFICATION,
		     static_cast<message_handler>(&NetworkSystem::handleAuthentification));
  loadMessageHandler(ClientMessages::KEY_INPUT_DATA,
		     static_cast<message_handler>(&NetworkSystem::handleKeyInputData));
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
  if (_isAuthentified)
    _client->run();
}

void            NetworkSystem::postRoutine(void)
{}

void		NetworkSystem::handleAuthentification(void *messageData)
{
  std::pair<std::string, unsigned int>	*p =
    static_cast<std::pair<std::string, unsigned int>* >(messageData);

  _client->connectToServer(p->first, p->second);
  _isAuthentified = true;
}

void		NetworkSystem::handleKeyInputData(void *messageData)
{
  IGui::Key	*key = static_cast<IGui::Key*>(messageData);  

  _client->connectToServer(p->first, p->second);
  _isAuthentified = true;
}
