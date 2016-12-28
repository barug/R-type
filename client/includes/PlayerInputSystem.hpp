
#ifndef _PLAYER_INPUT_SYSTEM_HPP_
# define _PLAYER_INPUT_SYSTEM_HPP_

# include "ASystem.hpp"
# include "IGui.hpp"
# include "GuiSystem.hpp"

class		playerInputSystem : public ASystem
{
  IGui::Key	_lastKey;
  
public:
  PlayerInputSystem(EntityManager &entityManager, MessageBus &MessageBus);
  virtual void		preRoutine() {}
  virtual void		updateEntity(int entityId);
  virtual void		postRoutine() {}
  void			handleNewKeyInput(void *messageData);
};

#endif /* !_PLAYER_INPUT_SYSTEM_HPP_ */
