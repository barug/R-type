
#include "PlayerInputSystem.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include <iostream>

const std::string PlayerInputSystem::name = "PlayerInputSystem";

PlayerInputSystem::PlayerInputSystem(EntityManager &entityManager,
				     MessageBus &MessageBus)
  : ASystem(entityManager, MessageBus),
    _lastKey(IGui::Key::NONE)
{
  loadMessageHandler(GuiSystem::Messages::KEY_INPUT_DATA,
  		     static_cast<message_handler>(&PlayerInputSystem::handleNewKeyInput));
  int playerShipId = _entityManager.createEntity("PlayerShip");
  std::cout << "created ship with id: " << playerShipId << std::endl;

  PhysicComponent *physComp =
    static_cast<PhysicComponent*>(_entityManager.getComponent(playerShipId,
  							      "PhysicComponent"));
  SpriteComponent *spriteComp =
    static_cast<SpriteComponent*>(_entityManager.getComponent(playerShipId,
  							      "SpriteComponent"));
  PositionComponent *positionComp =
    static_cast<PositionComponent*>(_entityManager.getComponent(playerShipId,
  							      "PositionComponent"));
  positionComp->setX(10);
  positionComp->setY(10);
  physComp->setSpeedX(0);
  physComp->setSpeedY(0);
  physComp->setAccelerationX(0);
  physComp->setAccelerationY(0);
  spriteComp->setPathAnimated("./assets/sprites/r-typesheet42.gif");
  spriteComp->setEntityName("PlayerShip");
  spriteComp->setRec({166/5, 0, 166/5, 17}, 5);
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
  if (_lastKey == IGui::Key::UP)
    physComp->setAccelerationY(-1);
  if (_lastKey == IGui::Key::DOWN)
    physComp->setAccelerationY(1);
  if (_lastKey == IGui::Key::LEFT)
    physComp->setAccelerationX(-1);
  if (_lastKey == IGui::Key::RIGHT)
    physComp->setAccelerationX(1);
}

void		PlayerInputSystem::postRoutine()
{
  _lastKey = IGui::Key::NONE;
}


void		PlayerInputSystem::handleNewKeyInput(void *messageData)
{
  IGui::Key	*key = static_cast<IGui::Key*>(messageData);

  std::cout << "getting new input message" << std::endl;
  _lastKey = *key;
}
