
#include "PlayerInputSystem.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "HitBoxComponent.hpp"
#include "HealthComponent.hpp"
#include "ScriptComponent.hpp"
#include "BasicMonsterScript.hpp"
#include <iostream>

const std::string PlayerInputSystem::name = "PlayerInputSystem";

PlayerInputSystem::PlayerInputSystem(EntityManager &entityManager,
				     MessageBus &MessageBus)
  : ASystem(entityManager, MessageBus),
    _lastKey(IGui::Key::NONE)
{
  loadMessageHandler(ClientMessages::KEY_INPUT_DATA,
  		     static_cast<message_handler>(&PlayerInputSystem::handleNewKeyInput));
  _entityManager.createEntity("PlayerShip", 100, 400);
}

void		PlayerInputSystem::updateEntity(int entityId)
{
  PlayerInputComponent *inputComp =
    static_cast<PlayerInputComponent*>(_entityManager.getComponent(entityId,
  								   PlayerInputComponent::name));
  PhysicComponent *physComp =
    static_cast<PhysicComponent*>(_entityManager.getComponent(entityId,
							      PhysicComponent::name));
  PositionComponent *playerPosComp =
    static_cast<PositionComponent*>(_entityManager.getComponent(entityId,
								PositionComponent::name));

  physComp->setAccelerationX(0);
  physComp->setAccelerationY(0);
  if (_lastKey == IGui::Key::UP)
    physComp->setSpeedY(physComp->getSpeedY() - 0.5);
  if (_lastKey == IGui::Key::DOWN)
    physComp->setSpeedY(physComp->getSpeedY() + 0.5);
  if (_lastKey == IGui::Key::LEFT)
    physComp->setSpeedX(physComp->getSpeedX() - 0.5);
  if (_lastKey == IGui::Key::RIGHT)
    physComp->setSpeedX(physComp->getSpeedX() + 0.5);
  if(_lastKey == IGui::Key::SPACE)
    {
      std::chrono::time_point<std::chrono::system_clock> now =
	std::chrono::system_clock::now();
      std::chrono::time_point<std::chrono::system_clock> lastFire =
	inputComp->getLastFire();
      int elapsed =
	std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFire).count();
      if (elapsed > 250)
	{
	  inputComp->setLastFire(now);
	  _entityManager.createEntity("basicProjectile",
				      playerPosComp->getX() + 20,
				      playerPosComp->getY(),
				      15,
				      std::vector<unsigned int>({208/12,
					    0,
					    208/12,
					    18}).data(),
				      12,
				      HealthComponent::Faction::PLAYERS,
				      "./assets/sprites/r-typesheet3.png");
	}
    }
}

void		PlayerInputSystem::postRoutine()
{
  _lastKey = IGui::Key::NONE;
}


void		PlayerInputSystem::handleNewKeyInput(void *messageData)
{
  IGui::Key	*key = static_cast<IGui::Key*>(messageData);

  _lastKey = *key;
}
