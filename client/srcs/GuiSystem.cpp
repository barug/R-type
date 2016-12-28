# include "GuiSystem.hpp"
# include "SpriteComponent.hpp"
# include "PositionComponent.hpp"
# include "Window.hpp"

GuiSystem::GuiSystem(EntityManager &entityManager, MessageBus &messageBus)
  : ASystem(entityManager, messageBus),
    _gui(new Window("RType", 800, 600, "./assets/font/digital.otf")),
    _rtypeUI(*_gui),
    _ip(),
    _port(),
    _contextHandler({{RTypeUI::Context::Introduction,            &GuiSystem::_handleIntroduction},
                     {RTypeUI::Context::Authentification,        &GuiSystem::_handleAuthentification},
                     {RTypeUI::Context::WaitingRoom,             &GuiSystem::_handleWaitingRoom},
                     {RTypeUI::Context::Game,                    &GuiSystem::_handleGame},
                     {RTypeUI::Context::Loading,                 &GuiSystem::_handleLoading}})
{}

GuiSystem::~GuiSystem()
{}

void            GuiSystem::preRoutine(void)
{
  _gui->clear();
  _gui->handleEvents();
  if (_gui->getKey() != IGui::Key::NONE)
    _messageBus.post(GuiSystem::Messages::KEY_INPUT_DATA, new IGui::Key(_gui->getKey()));
  ((*this).*(_contextHandler[_rtypeUI.getContext()]))();
}

void            GuiSystem::updateEntity(int entityId)
{
  SpriteComponent *spriteComponent =
    static_cast<SpriteComponent*>(_entityManager.getComponent(entityId, "SpriteComponent"));
  PositionComponent *positionComponent =
    static_cast<PositionComponent*>(_entityManager.getComponent(entityId, "PositionComponent"));
  // AnimationComponent *animationComponent =
  //   static_cast<AnimationComponent*>(_entityManager.getComponent(entityId, "AnimationComponent"));
  _gui->setTextureAt(spriteComponent->getPath(), positionComponent->getX(), positionComponent->getY());
}

void            GuiSystem::postRoutine(void)
{
  _gui->display();
}

void            GuiSystem::_handleIntroduction(void)
{
  _rtypeUI.displayIntroduction();
}

void            GuiSystem::_handleAuthentification(void)
{
  _rtypeUI.displayAuthentification(&_ip, &_port);
  if (!_ip.empty() && _rtypeUI.getContext() != RTypeUI::Context::Authentification)
    {
      std::cout << "ip == > " << _ip << " et " << _port << std::endl;
    }
}

void            GuiSystem::_handleWaitingRoom(void)
{
  _rtypeUI.displayWaitingRoom();
}

void            GuiSystem::_handleGame(void)
{
  _rtypeUI.displayGame();

}

void            GuiSystem::_handleLoading(void)
{
  _rtypeUI.displayLoading();
}
