
#include "PlayerInputSystem.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "HitBoxComponent.hpp"
#include "HealthComponent.hpp"
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
  							      PhysicComponent::name));
  SpriteComponent *spriteComp =
    static_cast<SpriteComponent*>(_entityManager.getComponent(playerShipId,
  							      SpriteComponent::name));
  PositionComponent *positionComp =
    static_cast<PositionComponent*>(_entityManager.getComponent(playerShipId,
								PositionComponent::name));
  HitBoxComponent *hitBoxComp =
    static_cast<HitBoxComponent*>(_entityManager.getComponent(playerShipId,
  							      HitBoxComponent::name));
  HealthComponent *healthComp =
    static_cast<HealthComponent*>(_entityManager.getComponent(playerShipId,
							      HealthComponent::name));
  positionComp->setX(10);
  positionComp->setY(10);
  physComp->setSpeedX(0);
  physComp->setSpeedY(0);
  physComp->setAccelerationX(0);
  physComp->setAccelerationY(0);
  spriteComp->setPathAnimated("./assets/sprites/r-typesheet42.gif");
  spriteComp->setEntityName("PlayerShip");
  spriteComp->setRec({166/5, 0, 166/5, 17}, 5);
  healthComp->setHealth(0);
  healthComp->setDamagePower(0);
  healthComp->setFaction(HealthComponent::Faction::PLAYERS);

  int basicMonsterId = _entityManager.createEntity("BasicMonster");
  spriteComp =
    static_cast<SpriteComponent*>(_entityManager.getComponent(basicMonsterId,
  							      SpriteComponent::name));
  positionComp =
    static_cast<PositionComponent*>(_entityManager.getComponent(basicMonsterId,
        							PositionComponent::name));
  hitBoxComp =
    static_cast<HitBoxComponent*>(_entityManager.getComponent(basicMonsterId,
  							      HitBoxComponent::name));
  healthComp =
    static_cast<HealthComponent*>(_entityManager.getComponent(playerShipId,
							      HealthComponent::name));
  spriteComp->setPathAnimated("./assets/sprites/r-typesheet17.gif");
  spriteComp->setEntityName("BasicMonster");
  spriteComp->setRec({66, 0, 61, 132}, 8);
  positionComp->setX(300);
  positionComp->setY(300);
  hitBoxComp->setCircleRadius(20);
  healthComp->setHealth(1);
  healthComp->setDamagePower(-1);
  healthComp->setFaction(HealthComponent::Faction::ENEMIES);
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
