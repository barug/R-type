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

bool			RTypeClient::tryToAuthenticate()
{
  if (_networkHandler->getSocket().somethingToRead())
    {
      _isAuthentified = true;
      std::shared_ptr<ISocket::Datagram>	data;
      
      data = _networkHandler->getSocket().readSocket();
	
      Message*			message = new Message(*data);

      std::cout << "SOMETHING TO READ" << std::endl;
      if (_commandHandler->execFuncByOperationCode(this, message, 0) != true)
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

bool	RTypeClient::run()
{
  if (_networkHandler->getSocketGame().somethingToRead())
    {
      std::shared_ptr<ISocket::Datagram>	data;
      data = _networkHandler->getSocketGame().readSocket();
      Message*			message = new Message(*data);

      std::cout << "SOMETHING TO READ" << std::endl;
      if (_commandHandler->execFuncByOperationCode(this, message, 0) != true)
	return false;
      return true;
    }
  else if (_networkHandler->getSocket().somethingToRead())
    {
      std::shared_ptr<ISocket::Datagram>	data;
      data = _networkHandler->getSocket().readSocket();
      Message*			message = new Message(*data);

      std::cout << "SOMETHING TO READ" << std::endl;
      if (_commandHandler->execFuncByOperationCode(this, message, 1) != true)
	return false;
      return true;
    }
  return true;
}
