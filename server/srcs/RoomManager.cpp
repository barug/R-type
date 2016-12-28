# include	<string>

# include	"Client.hpp"
# include	"ISocket.hpp"

# include	"RoomManager.hpp"

RoomManager::RoomManager(std::shared_ptr<NetworkHandler> networkHandler) :
  _networkHandler(networkHandler),
  _roomNumber(0),
  _gameRooms()
{
  for (int i = 0; i < MAX_ROOM; i++)
    {
      _gameRooms.insert( std::make_pair( "Room " + std::to_string( i ),
					 std::make_shared< Room >( "Room " + std::to_string( i ) ) ) );
      _roomNumber++;
    }
}

RoomManager::~RoomManager()
{
  for (auto it : _gameRooms)
    {
      it.second->setRun(false);
      _gameRooms.erase(it.first);
    }
}

int	RoomManager::getRoomNumber() const
{
  return _roomNumber;
}

void	RoomManager::setRoomNumber(int value)
{
  _roomNumber = value;
}

const std::map< const std::string, std::shared_ptr< Room > >	RoomManager::getGameRooms() const
{
  return _gameRooms;
}

Room *	RoomManager::getRoomById(const std::string id) const
{

  if (_gameRooms.find(id) == _gameRooms.end())
    return nullptr;
  return _gameRooms.find(id)->second.get();
}

Room *	RoomManager::createRoom(const std::string name)
{
  auto		it = _gameRooms.find(name);

  if (it == _gameRooms.end())
    _gameRooms.insert(std::make_pair(name, std::make_shared<Room>(name)));
  return _gameRooms[name].get();
}

void	RoomManager::checkRoom()
{
  for (auto it : _gameRooms)
    if (it.second->getRun() == false)
      _gameRooms.erase(it.first);
}
