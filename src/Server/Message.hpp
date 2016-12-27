#ifndef		__MESSAGE_HPP__
# define	__MESSAGE_HPP__

# define	STRUCT_SIZE (6)

# include	<vector>
# include	<memory>
# include	<string>

# include	"ISocket.hpp"

class		Message
{

public:

  explicit				Message(int opCode,
						const std::string & ip,
						int port,
						void * data = NULL,
						int size = 0);
  explicit				Message(const ISocket::Datagram & data);
  ~Message();

  int					getOperationCode() const ;
  int					getSize() const;
  char *				getData() const;
  const std::string &			getIp() const;
  int					getPort() const;

  std::shared_ptr< ISocket::Datagram >	createDatagram() ;

private:

  char			*_data;
  int			_operationCode;
  int			_size;
  std::string		_ip;
  int			_port;
  ISocket::Datagram	_datagram;

public :

# pragma pack(push, 1)
# define	SIZE_HEADER (8)
  struct	Header
  {
    int		_size;
    int		_opCode;
  };

  struct	Entity
  {
    std::string	_name;
    int		_pos_x;
    int		_pos_y;
  };

  struct		Entitys
  {
    int			_nbEntitys;
    std::vector<Entity>	_Entitys;
  };

  struct		Room
  {
    std::string		_ip;
    int			_port;
    std::string		_name;
    int			_nbPlayer;
    std::vector<Entity>	_players;
  };

  struct		ListOfRoom
  {
    int			_nbRoom;
    std::vector<Room>	_listOfRoom;
  };
# pragma pack(pop)

};

#endif		// !__MESSAGE_HPP__
