# include	<thread>
# include	<iostream>

# include	<memory>

# include	"RTypeClient.hpp"
# include	"Message.hpp"

RTypeClient::RTypeClient() :
  _networkHandler(std::make_shared<NetworkHandler>()),
  _commandHandler(std::make_unique<CommandHandler>()),
  _askedForAuth(false),
  _isAuthentified(false)
{
}

RTypeClient::RTypeClient(const std::string ip, const int port) :
  _networkHandler(std::make_shared<NetworkHandler>(ip, port)),
  _commandHandler(std::make_unique<CommandHandler>()),
  _askedForAuth(false),
  _isAuthentified(false)
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
      // std::cout << "RTypeClient::run isnt auth" << std::endl;
      if (_askedForAuth)
	{
	  std::cout << "RTypeClient::run asked for auth" << std::endl;
	  _askedForAuth = false;
	}
      return false;
    }
  return true;
}
