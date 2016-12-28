//
// rtype
//

#ifndef                 __CORE_HPP__
# define                __CORE_HPP__

# include               <map>
# include               <memory>
# include               "RTypeUI.hpp"
# include               "RTypeClient.hpp"
# include		"GameEngine.hpp"

class                   Core
{
public:
  explicit              Core(int ac, char **av);
                        ~Core();

  void                  gameLoop();

private:
  void                  _handleIntroduction(void);
  void                  _handleStartScreen(void);
  void                  _handleAuthentification(void);
  void                  _handleWaitingRoom(void);
  void                  _handleGame(void);
  void                  _handleLoading(void);
  bool                  _checkArgs(int ac, char **av);

private:

  std::shared_ptr<IGui> _gui;
  std::unique_ptr<RTypeClient> _client;
  RTypeUI               _rtypeUI;
  std::string           _ip;
  unsigned int          _port;
  std::map<RTypeUI::Context, void (Core::* )(void)> _contextHandler;
  GameEngine		_gameEngine;
};

#endif                  // !__CORE_HPP__
