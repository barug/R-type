# include	<iostream>
# include       "NetworkSystem.hpp"
# include	"GuiSystem.hpp"
# include	"../includes_ecs/UnixSocket.hpp"

const std::string NetworkSystem::name = "NetworkSystem";

NetworkSystem::NetworkSystem(EntityManager &entityManager, MessageBus &messageBus)
  : ASystem(entityManager, messageBus),
    _clients(),
    _hasGameStarted(false)
{
  loadMessageHandler(ServerMessages::ADD_CLIENT,
		     static_cast<message_handler>(&NetworkSystem::handleAddClient));
}

NetworkSystem::~NetworkSystem()
{}

void            NetworkSystem::preRoutine(void)
{
  if (_clients.size() > 1 && )
    {
      std::cout << "More than 1 client" << std::endl;
      for (auto it : _clients)
	{
	  std::shared_ptr<Message> pM = std::make_shared<Message>(5, it.first, it.second);

	  std::shared_ptr<UnixSocket> pS = std::make_shared<UnixSocket>(it.first, it.second);
	  std::cout << "datagram ready" << std::endl;
	  pS->writeSocket(*(pM->createDatagram()));
	  std::cout << "data sent" << std::endl;
	}
    }
}

void            NetworkSystem::updateEntity(int entityId)
{
}

void            NetworkSystem::postRoutine(void)
{}

void		NetworkSystem::handleAddClient(void *messageData)
{
  std::pair<std::string, int> *p = static_cast<std::pair<std::string, int> *>(messageData);

  std::cout << p->first << " " << p->second << std::endl;
  _clients.push_back(std::pair<std::string, int>(*p));
}

