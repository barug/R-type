
#include "PlayerInputSystem.hpp"

PlayerInputSystem::PlayerInputSystem(EntityManager &entityManager,
				     MessageBus &MessageBus)
  : ASystem(entityManager, MessageBus),
    _lastKey(IGui::Key::NONE)
{
  // loadMessageHandler(GuiSystem::Messages::KEY_INPUT_DATA,
  // 		     static_cast<message_handler>(&PlayerInputSystem::handleNewKeyInput));
  // int playerShipId = _entityManager.createEntity("PlayerShip");
  // PhysicComponent *physComp =
  //   static_cast<PhysicComponent*>(_entityManager.getComponent(playerShipId,
  // 							      "PhysicComponent"));
  // SpriteComponent *spriteComp =
  //   static_cast<SpriteComponent*>(_entityManager.getComponent(entityId,
  // 							      "SpriteComponent"));
  // PositionComponent *positionComp =
  //   static_cast<PositionComponent*>(_entityManager.getComponent(entityId,
  // 							      "PositionComponent"));
  // positionComp.setX(10);
  // positionComp.setY(10);
  // physComp.setSpeedX(0);
  // physComp.setSpeedY(0);
  // physComp.setAccelerationX(0);
  // physComp.setAccelerationY(0);
  // spriteComp.setPath("../assets/sprites/r-typesheet1.gif");
}

void		PlayerInputSystem::updateEntity(int entityId)
{
  // PlayerInputComponent *inputComp =
  //   static_cast<PlayerInputComponent*>(_entityManager.getComponent(entityId,
  // 								   "PlayerInputComponent"));
  PhysicComponent *physComp =
    static_cast<PhysicComponent*>(_entityManager.getComponent(entityId,
							      "PhysicComponent"));

  physComp->setAccelerationX(0);
  physComp->setAccelerationY(0);
  if (_lastKey == IGui::Key::K_Z)
    physComp->setAccelerationY(-10);
  if (_lastKey == IGui::Key::K_S)
    physComp->setAccelerationY(10);
  if (_lastKey == IGui::Key::K_Q)
    physComp->setAccelerationX(-10);
  if (_lastKey == IGui::Key::K_D)
    physComp->setAccelerationY(10);
}

void		PlayerInputSystem::handleNewKeyInput(void *messageData)
{
  IGui::Key	*key = static_cast<IGui::Key*>(messageData);

  _lastKey = *key;
}
