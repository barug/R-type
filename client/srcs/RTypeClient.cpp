# include	<thread>
# include	<iostream>

# include	<memory>

# include	"../includes/RTypeClient.hpp"
# include	"Message.hpp"

RTypeClient::RTypeClient() :
  _networkHandler(std::make_shared<NetworkHandler>()),
  _commandHandler(std::make_unique<CommandHandler>()),
  _askedForAuth(false),
  _isAuthentified(false),
  _hasGameStarted(false)
{
}

RTypeClient::RTypeClient(const std::string ip, const int port) :
  _networkHandler(std::make_shared<NetworkHandler>(ip, port)),
  _commandHandler(std::make_unique<CommandHandler>()),
  _askedForAuth(false),
  _isAuthentified(false),
  _hasGameStarted(false)
{
  // create the co cmd
  std::unique_ptr< Message >	message =
    std::make_unique< Message >(101,
                                _networkHandler->getSocket().getIpServer(),
                                _networkHandler->getSocket().getPortServer());
  // write  the co cmd
  _networkHandler->getSocket().writeSocket(*message->createDatagram());
}

RTypeClient::~RTypeClient()
{}

NetworkHandler*   RTypeClient::getNetworkHandler() const
{
  return _networkHandler.get();
}

void		        RTypeClient::setNetworkHandler(std::shared_ptr<NetworkHandler> &ptr)
{
  _networkHandler = ptr;
}

bool			RTypeClient::connectToServer(const std::string &ip, const int port)
{
  _networkHandler->getSocket().connectToServer(ip, port);
  std::unique_ptr< Message >	message =
    std::make_unique< Message >(101,
                                _networkHandler->getSocket().getIpServer(),
                                _networkHandler->getSocket().getPortServer());
  _networkHandler->getSocket().writeSocket(*message->createDatagram());
  _askedForAuth = true;
  return true;
}

void			RTypeClient::setGameStarted(bool state)
{
  _hasGameStarted = state;
}

bool	RTypeClient::run()
{
  if (_networkHandler->getSocket().somethingToRead())
    {
      _isAuthentified = true;      
      const std::shared_ptr<ISocket::Datagram>	data = _networkHandler->getSocket().readSocket();

      Message*			message = new Message(*data);

      if (_commandHandler->execFuncByOperationCode(this, message) != true)
	return false;
      return true;
    }
  if (!_isAuthentified)
    {
      if (_askedForAuth)
	_askedForAuth = false;
      return false;
    }
  return true;
}
