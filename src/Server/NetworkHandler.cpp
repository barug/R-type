# include	<iterator>

# include	"NetworkHandler.hpp"
# include	"UnixSocket.hpp"
# include	"WinSocket.hpp"

NetworkHandler::NetworkHandler(const int port) :
  _client(),
# ifdef		__unix__
  _socket(std::make_unique<UnixSocket>("0", port))
# elif		defined(_WIN32) || defined(WIN32)
  _socket(std::make_unique< WinSocket>("0", port))
# define	OS_Windows
# endif
{}

NetworkHandler::~NetworkHandler()
{}

ISocket&	NetworkHandler::getSocket() const
{
  return *(_socket).get();
}

const std::map< std::string, std::shared_ptr< Client > >&	NetworkHandler::getClient() const
{
  return _client;
}

# include <iostream>

Client*		NetworkHandler::addClient(const std::string& key, const std::string& ip, int port)
{
  auto		it = _client.find(key);

  std::cout << " [+] New player in tows " << ip << ":" << port << std::endl;

  if (it == _client.end())
    _client.insert(std::make_pair(key, std::make_shared<Client>(ip, port)));
  return _client[key].get();
}

Client*		NetworkHandler::getClientByKey(const std::string & key) const
{
  for ( std::map< std::string, std::shared_ptr< Client > >::const_iterator it = _client.begin();
	it != _client.end();
	++it )
    if (it->first == key)
      return (it->second).get();
  return NULL;
}
