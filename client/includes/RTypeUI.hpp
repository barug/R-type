//
// rtype
//

#ifndef         __RTYPE_UI_HPP__
# define        __RTYPE_UI_HPP__

# include       "IGui.hpp"
# include       "Timer.hpp"

class           RTypeUI
{
public:
  enum          Context
    {
      Introduction = 0,
      Authentification = 1,
      WaitingRoom = 2,
      Game = 3,
      Loading = 4,
      Menu = 5
    };

  explicit              RTypeUI(IGui &gui);
                        ~RTypeUI();

  void                  setContext(const RTypeUI::Context context);
  RTypeUI::Context      getContext(void) const;

  void                  displayIntroduction(void);
  void                  displayAuthentification(std::string *ip, unsigned int *port);
  void                  displayLoading(void);
  void                  displayWaitingRoom(void);
  void                  displayGame(void);
  void                  displayMenu(void);

private:
  IGui                  &_gui;
  Timer                 *_timer;
  Context               _context;
};

#endif          // !__RTYPE_UI_HPP__
