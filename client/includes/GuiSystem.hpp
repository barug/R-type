#ifndef         __GUI_SYSTEM_HPP__
# define        __GUI_SYSTEM_HPP__

# include       "ASystem.hpp"
# include       "IGui.hpp"
# include       "RTypeUI.hpp"

class           GuiSystem : public ASystem
{
  // ui
  IGui          *_gui;
  RTypeUI       _rtypeUI;

  // network transition
  std::string   _ip;
  unsigned int  _port;

  // map type
  typedef std::map<std::string, std::pair<Animation, AnimatedSprite *> > AnimationMap;
  AnimationMap                                          _animationHandler;
  std::map<RTypeUI::Context, void (GuiSystem::* )(void)>_contextHandler;

  void          _handleIntroduction(void);
  void          _handleAuthentification(void);
  void          _handleWaitingRoom(void);
  void          _handleGame(void);
  void          _handleLoading(void);

public:

  static const std::string	name;

  enum		Messages
    {
      KEY_INPUT_DATA = 11
    };

  explicit      GuiSystem(EntityManager &entityManager, MessageBus &messageBus);
  virtual       ~GuiSystem();
  virtual void  preRoutine(void);
  virtual void  updateEntity(int entityId);
  virtual void  postRoutine(void);

  GuiSystem(const GuiSystem &) = delete;
  GuiSystem& operator=(const GuiSystem &) = delete;
};

#endif          // !__GUI_SYSTEM_HPP__
