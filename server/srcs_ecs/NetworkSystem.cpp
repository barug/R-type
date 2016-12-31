# include	<iostream>
# include       "NetworkSystem.hpp"
# include	"GuiSystem.hpp"

const std::string NetworkSystem::name = "NetworkSystem";

NetworkSystem::NetworkSystem(EntityManager &entityManager, MessageBus &messageBus)
  : ASystem(entityManager, messageBus),
    _clients(),
    _isAuthentified(false)
{
  loadMessageHandler(ServerMessages::ADD_CLIENT,
		     static_cast<message_handler>(&NetworkSystem::handleAddClient));
}

NetworkSystem::~NetworkSystem()
{}

void            NetworkSystem::preRoutine(void)
{
}

void            NetworkSystem::updateEntity(int entityId)
{
  for (auto it : clients)
    it->run();
}

void            NetworkSystem::postRoutine(void)
{}

void		NetworkSystem::handleAddClient(void *messageData)
{
  std::pair<std::string, int> *p = static_cast<std::pair<std::string, int> *>(messageData);

  std::cout << p->first << " " << p->second << std::endl;
  std::shared_ptr<RTypeClient>	newClient = std::make_shared<RTypeClient>(p->first, p->second);
  _clients.push_back(newClient);
}

