#ifndef			__ROOMMANAGER_HPP__
# define		__ROOMMANAGER_HPP_

# include		<memory>
# include		<list>
# include		<string>

# include		"Room.hpp"
# include		"NetworkHandler.hpp"

# define		MAX_ROOM (20)

class			Room;

class			RoomManager
{

 public :

  explicit							RoomManager(std::shared_ptr< NetworkHandler >
									    networkHandler);
  ~RoomManager();

  int								getRoomNumber() const;
  void								setRoomNumber(int value);
  const std::map< const std::string, std::shared_ptr< Room > >	getGameRooms() const;

  Room *							getRoomById(const std::string id) const;
  Room *							createRoom(const std::string name);

  void								checkRoom();

private :

  std::shared_ptr< NetworkHandler >				_networkHandler;
  int								_roomNumber;
  std::map< const std::string, std::shared_ptr< Room > >	_gameRooms;

};

# endif			// !__ROOMMANAGER_HPP_
