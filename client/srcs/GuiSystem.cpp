# include "GuiSystem.hpp"
# include "NetworkSystem.hpp"
# include "SpriteComponent.hpp"
# include "PositionComponent.hpp"
# include "Window.hpp"
# include "Audio.hpp"

const std::string	GuiSystem::name = "GuiSystem";

GuiSystem::GuiSystem(EntityManager &entityManager,
		     MessageBus &messageBus,
		     unsigned int winX,
		     unsigned int winY)
  : ASystem(entityManager, messageBus),
    _gui(new Window("RType", winX, winY, "./assets/font/digital.otf")),
    _audio(new Audio),
    _rtypeUI(*_gui),
    _ip(),
    _port(),
    _contextHandler({{RTypeUI::Context::Introduction,            &GuiSystem::_handleIntroduction},
                     {RTypeUI::Context::Authentification,        &GuiSystem::_handleAuthentification},
                     {RTypeUI::Context::WaitingRoom,             &GuiSystem::_handleWaitingRoom},
                     {RTypeUI::Context::Game,                    &GuiSystem::_handleGame},
                     {RTypeUI::Context::Loading,                 &GuiSystem::_handleLoading}})
{
  loadMessageHandler(ClientMessages::AUTHENTIFICATION_FAILED,
		     static_cast<message_handler>(&GuiSystem::_handleAuthFailed));
  loadMessageHandler(ClientMessages::AUTHENTIFICATION_SUCCESS,
		     static_cast<message_handler>(&GuiSystem::_handleAuthSuccess));
  _audio->loadMusic("./assets/sound/yasuo.wav");
  _audio->musicSetVolume(100);
  _audio->musicSetLoop(true);
}

GuiSystem::~GuiSystem()
{}

void            GuiSystem::preRoutine(void)
{
  _gui->clear();
  _gui->handleEvents();
  if (_gui->getKey() != IGui::Key::NONE)
    _messageBus.post(ClientMessages::KEY_INPUT_DATA, new IGui::Key(_gui->getKey()));
  ((*this).*(_contextHandler[_rtypeUI.getContext()]))();
}

void            GuiSystem::updateEntity(int entityId)
{
  if (_rtypeUI.getContext() == RTypeUI::Context::Game)
    {
      SpriteComponent *spriteComponent =
        static_cast<SpriteComponent*>(_entityManager.getComponent(entityId,
								  SpriteComponent::name));
      PositionComponent *positionComponent =
        static_cast<PositionComponent*>(_entityManager.getComponent(entityId,
								    PositionComponent::name));

      auto it = _animationHandler.find(spriteComponent->getEntityName());
      if (it == _animationHandler.end())
        {
          if (spriteComponent->isFullFrames())
            spriteComponent->setAnimation(_gui->addFrames(spriteComponent->getPath(),
                                                          spriteComponent->getFullFrames()));
          else
            spriteComponent->setAnimation(_gui->addFrames(spriteComponent->getPath(),
                                                          spriteComponent->getNbFrames(),
                                                          spriteComponent->getFrames()));

          _animationHandler.insert(AnimationMap::value_type(spriteComponent->getEntityName(),
                                                            std::make_pair(spriteComponent->getAnimation(),
                                                                           spriteComponent->getAnimatedSprite())));
        }

      if (spriteComponent->isAnimated())
        {
	  try {
          auto it = _animationHandler.find(spriteComponent->getEntityName());
          if (it != _animationHandler.end())
            {
              _gui->updateAnimatedSprite(it->second.first, *it->second.second,
                                         positionComponent->getX() - (spriteComponent->getWidth() / 2),
                                         positionComponent->getY() - (spriteComponent->getHeight() / 2));
            }
	  }
	  catch (std::exception &e)
	    {
	      std::cout << "gui exception: " << e.what() << std::endl;
	    }
        }
      else
        {
          _gui->setTextureAt(spriteComponent->getPath(), positionComponent->getX(), positionComponent->getY());
        }
    }
}

void            GuiSystem::postRoutine(void)
{
  _gui->update();
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
      _messageBus.post(ClientMessages::AUTHENTIFICATION, new std::pair<std::string, unsigned int>(_ip, _port));
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

void		GuiSystem::_handleAuthFailed(void *messageData)
{
  _rtypeUI.setContext(RTypeUI::Context::Authentification);
}

void		GuiSystem::_handleAuthSuccess(void *messageData)
{
  _rtypeUI.setContext(RTypeUI::Context::Game);
}
