# include	<iostream>
# include       "../includes_ecs/NetworkSystem.hpp"
# include	"../includes_ecs/GuiSystem.hpp"
# include	"../includes_ecs/UnixSocket.hpp"

const std::string NetworkSystem::name = "NetworkSystem";

NetworkSystem::NetworkSystem(EntityManager &entityManager, MessageBus &messageBus)
  : ASystem(entityManager, messageBus),
    _socketRoom(),
    _clients(),
    _hasGameStarted(false)
{
  loadMessageHandler(ServerMessages::ADD_CLIENT,
		     static_cast<message_handler>(&NetworkSystem::handleAddClient));
  loadMessageHandler(ServerMessages::SOCKET_ROOM,
		     static_cast<message_handler>(&NetworkSystem::handleSetSocketRoom));
}

NetworkSystem::~NetworkSystem()
{}

void            NetworkSystem::preRoutine(void)
{
  if (_clients.size() > 1 && !_hasGameStarted)
    {
      std::cout << "More than 1 client" << std::endl;
      for (auto it : _clients)
	{
	  std::shared_ptr<Message> pM = std::make_shared<Message>(5, it.first, it.second);

	  std::cout << _socketRoom->getIpServer() << std::endl;
	  std::cout << _socketRoom->getPortServer() << std::endl;
	  _socketRoom->writeSocket(*(pM->createDatagram()));
	}
      _hasGameStarted = true;
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

void		NetworkSystem::handleSetSocketRoom(void *messageData)
{
  std::pair<std::string, int> *p = static_cast<std::pair<std::string, int> *>(messageData);

  std::shared_ptr<UnixSocket> tmp = std::make_shared<UnixSocket>(p->first, p->second);

  // std::cout << tmp->getIpServer() << std::endl;
  // std::cout << tmp->getIp() << std::endl;
  // std::cout << tmp->getPortServer() << std::endl;
  // std::cout << tmp->getPort() << std::endl;
  setSocketRoom(tmp);
}


void		NetworkSystem::setSocketRoom(std::shared_ptr<ISocket> socketRoom)
{
  _socketRoom = socketRoom;
}
