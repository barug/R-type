
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
  PlayerInputComponent *playerComp =
    static_cast<PlayerInputComponent*>(_entityManager.getComponent(playerShipId,
								   PlayerInputComponent::name));
  positionComp->setX(100);
  positionComp->setY(400);
  physComp->setSpeedX(0);
  physComp->setSpeedY(0);
  physComp->setAccelerationX(0);
  physComp->setAccelerationY(0);
  physComp->setCanLeaveScreen(false);
  spriteComp->setPathAnimated("./assets/sprites/r-typesheet42.png");
  spriteComp->setEntityName("PlayerShip");
  spriteComp->setFrames({166/5, 0, 166/5, 17}, 5);
  // ou
  // spriteComp->setFrames({
  //     {166/5, 0, 166/5, 17},
  //       {(166/5)*2, 0, 166/5, 17},
  //         {(166/5)*3, 0, 166/5, 17},
  //           {(166/5)*4, 0, 166/5, 17},
  //             {(166/5)*5, 0, 166/5, 17}}
  //   );
  healthComp->setHealth(1);
  healthComp->setDamagePower(0);
  healthComp->setFaction(HealthComponent::Faction::PLAYERS);
  playerComp->setLastFire(std::chrono::system_clock::now());
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
    static_cast<HealthComponent*>(_entityManager.getComponent(basicMonsterId,
							      HealthComponent::name));
  physComp =
    static_cast<PhysicComponent*>(_entityManager.getComponent(basicMonsterId,
  							      PhysicComponent::name));
  ScriptComponent *scriptComp =
    static_cast<ScriptComponent*>(_entityManager.getComponent(basicMonsterId,
  							      ScriptComponent::name));

  spriteComp->setPathAnimated("./assets/sprites/r-typesheet17.png");
  spriteComp->setEntityName("BasicMonster");
  spriteComp->setFrames({66, 0, 61, 132}, 8);
  positionComp->setX(1150);
  positionComp->setY(400);
  physComp->setSpeedX(-2);
  physComp->setSpeedY(-2);
  physComp->setCanLeaveScreen(true);
  hitBoxComp->setCircleRadius(20);
  healthComp->setHealth(1);
  healthComp->setDamagePower(-1);
  healthComp->setFaction(HealthComponent::Faction::ENEMIES);
  scriptComp->setScript(new BasicMonsterScript(entityManager, basicMonsterId));
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
	  int projectileId = _entityManager.createEntity("playerBasicProjectile");
	  PositionComponent *projectilePosComp =
	    static_cast<PositionComponent*>(_entityManager.getComponent(projectileId,
									PositionComponent::name));
	  PhysicComponent *projectilePhysComp =
	    static_cast<PhysicComponent*>(_entityManager.getComponent(projectileId,
								      PhysicComponent::name));
	  HitBoxComponent *projectileHitBoxComp =
	    static_cast<HitBoxComponent*>(_entityManager.getComponent(projectileId,
								      HitBoxComponent::name));
	  SpriteComponent *projectileSpriteComp =
	    static_cast<SpriteComponent*>(_entityManager.getComponent(projectileId,
								      SpriteComponent::name));
	  HealthComponent *projectileHealthComp =
	    static_cast<HealthComponent*>(_entityManager.getComponent(projectileId,
								      HealthComponent::name));
	  projectilePosComp->setX(playerPosComp->getX() + 20);
	  projectilePosComp->setY(playerPosComp->getY());
	  projectilePhysComp->setSpeedX(15);
	  projectilePhysComp->setSpeedY(0);
	  projectilePhysComp->setCanLeaveScreen(true);
	  projectileHitBoxComp->setCircleRadius(10);
	  projectileSpriteComp->setPathAnimated("./assets/sprites/r-typesheet3.png");
	  projectileSpriteComp->setEntityName("playerBasicProjectile");
	  projectileSpriteComp->setFrames({208/12, 0, 208/12, 18}, 12);
	  projectileHealthComp->setHealth(1);
	  projectileHealthComp->setDamagePower(-1);
	  projectileHealthComp->setFaction(HealthComponent::Faction::PLAYERS);
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
