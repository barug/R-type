
#include "entityInitialiser.hpp"

void	initializePlayerShip(EntityManager &entityManager,
			     int entityId,
			     va_list args)
{
  PhysicComponent *physComp =
    static_cast<PhysicComponent*>(entityManager.getComponent(entityId,
  							      PhysicComponent::name));
  SpriteComponent *spriteComp =
    static_cast<SpriteComponent*>(entityManager.getComponent(entityId,
  							      SpriteComponent::name));
  PositionComponent *positionComp =
    static_cast<PositionComponent*>(entityManager.getComponent(entityId,
								PositionComponent::name));
  HitBoxComponent *hitBoxComp =
    static_cast<HitBoxComponent*>(entityManager.getComponent(entityId,
  							      HitBoxComponent::name));
  HealthComponent *healthComp =
    static_cast<HealthComponent*>(entityManager.getComponent(entityId,
							      HealthComponent::name));
  PlayerInputComponent *playerComp =
    static_cast<PlayerInputComponent*>(entityManager.getComponent(entityId,
								   PlayerInputComponent::name));
  int	x = va_arg(args, int);
  int	y = va_arg(args, int);

  positionComp->setX(x);
  positionComp->setY(y);
  physComp->setSpeedX(0);
  physComp->setSpeedY(0);
  physComp->setAccelerationX(0);
  physComp->setAccelerationY(0);
  physComp->setCanLeaveScreen(false);
  spriteComp->setPathAnimated("./assets/sprites/r-typesheet42.png");
  spriteComp->setEntityName("PlayerShip");
  spriteComp->setFrames({166/5, 0, 166/5, 17}, 5);
  healthComp->setHealth(1);
  healthComp->setDamagePower(0);
  hitBoxComp->setCircleRadius(10);
  healthComp->setFaction(HealthComponent::Faction::PLAYERS);
  playerComp->setLastFire(std::chrono::system_clock::now());

}
			     
void			initializeStrafingMonster(EntityManager &entityManager,
						  int entityId,
						  va_list args)
{
  SpriteComponent *spriteComp =
    static_cast<SpriteComponent*>(entityManager.getComponent(entityId,
  							      SpriteComponent::name));
  PositionComponent *positionComp =
    static_cast<PositionComponent*>(entityManager.getComponent(entityId,
        							PositionComponent::name));
  HitBoxComponent *hitBoxComp =
    static_cast<HitBoxComponent*>(entityManager.getComponent(entityId,
  							      HitBoxComponent::name));
  HealthComponent *healthComp =
    static_cast<HealthComponent*>(entityManager.getComponent(entityId,
							      HealthComponent::name));
  PhysicComponent *physComp =
    static_cast<PhysicComponent*>(entityManager.getComponent(entityId,
  							      PhysicComponent::name));
  ScriptComponent *scriptComp =
    static_cast<ScriptComponent*>(entityManager.getComponent(entityId,
  							      ScriptComponent::name));
  int	x = va_arg(args, int);
  int	y = va_arg(args, int);
  float	speedY = va_arg(args, int);
  spriteComp->setPathAnimated("./assets/sprites/r-typesheet17.png");
  spriteComp->setEntityName("BasicMonster");
  spriteComp->setFrames({66, 0, 61, 132}, 8);
  positionComp->setX(x);
  positionComp->setY(y);
  physComp->setSpeedX(-2);
  physComp->setSpeedY(speedY);
  physComp->setCanLeaveScreen(true);
  hitBoxComp->setCircleRadius(30);
  healthComp->setHealth(1);
  healthComp->setDamagePower(-1);
  healthComp->setFaction(HealthComponent::Faction::ENEMIES);
  scriptComp->setScript(new StrafingMonsterScript(entityManager, entityId));  
}

void			initializeBasicMonster(EntityManager &entityManager,
					       int entityId,
					       va_list args)
{
  SpriteComponent *spriteComp =
    static_cast<SpriteComponent*>(entityManager.getComponent(entityId,
  							      SpriteComponent::name));
  PositionComponent *positionComp =
    static_cast<PositionComponent*>(entityManager.getComponent(entityId,
        							PositionComponent::name));
  HitBoxComponent *hitBoxComp =
    static_cast<HitBoxComponent*>(entityManager.getComponent(entityId,
  							      HitBoxComponent::name));
  HealthComponent *healthComp =
    static_cast<HealthComponent*>(entityManager.getComponent(entityId,
							      HealthComponent::name));
  PhysicComponent *physComp =
    static_cast<PhysicComponent*>(entityManager.getComponent(entityId,
  							      PhysicComponent::name));
  ScriptComponent *scriptComp =
    static_cast<ScriptComponent*>(entityManager.getComponent(entityId,
  							      ScriptComponent::name));
  int	x = va_arg(args, int);
  int	y = va_arg(args, int);
  float	speedY = va_arg(args, int);
  spriteComp->setPathAnimated("./assets/sprites/r-typesheet17.png");
  spriteComp->setEntityName("BasicMonster");
  spriteComp->setFrames({66, 0, 61, 132}, 8);
  positionComp->setX(x);
  positionComp->setY(y);
  physComp->setSpeedX(-2);
  physComp->setSpeedY(speedY);
  physComp->setCanLeaveScreen(true);
  hitBoxComp->setCircleRadius(30);
  healthComp->setHealth(1);
  healthComp->setDamagePower(-1);
  healthComp->setFaction(HealthComponent::Faction::ENEMIES);
  scriptComp->setScript(new BasicMonsterScript(entityManager, entityId));  
}


void		initializeBasicProjectile(EntityManager &entityManager,
					  int entityId,
					  va_list args)
{
  PositionComponent *projectilePosComp =
    static_cast<PositionComponent*>(entityManager.getComponent(entityId,
								PositionComponent::name));
  PhysicComponent *projectilePhysComp =
    static_cast<PhysicComponent*>(entityManager.getComponent(entityId,
							      PhysicComponent::name));
  HitBoxComponent *projectileHitBoxComp =
    static_cast<HitBoxComponent*>(entityManager.getComponent(entityId,
							      HitBoxComponent::name));
  SpriteComponent *projectileSpriteComp =
    static_cast<SpriteComponent*>(entityManager.getComponent(entityId,
							      SpriteComponent::name));
  HealthComponent *projectileHealthComp =
    static_cast<HealthComponent*>(entityManager.getComponent(entityId,
								      HealthComponent::name));
  int	x = va_arg(args, int);
  int	y = va_arg(args, int);
  float	speedX = va_arg(args, int);
  float	speedY = va_arg(args, int);
  unsigned int *frameArray = va_arg(args, unsigned int*);
  std::vector<unsigned int> rec;
  rec.assign(frameArray, frameArray + 4);
  unsigned int nbFrames = va_arg(args, unsigned int);
  int faction = va_arg(args, int);
  char	*spritePath = va_arg(args, char *);

  projectilePosComp->setX(x);
  projectilePosComp->setY(y);
  projectilePhysComp->setSpeedX(speedX);
  projectilePhysComp->setSpeedY(speedY);
  projectilePhysComp->setCanLeaveScreen(true);
  projectileHitBoxComp->setCircleRadius(10);
  projectileSpriteComp->setPathAnimated(spritePath);
  projectileSpriteComp->setEntityName(spritePath);
  projectileSpriteComp->setFrames(rec, nbFrames);
  projectileHealthComp->setHealth(1);
  projectileHealthComp->setDamagePower(-1);
  projectileHealthComp->setFaction(static_cast<HealthComponent::Faction>(faction));
}

void		initializeMonsterSpawnScript(EntityManager &entityManager,
					     int entityId,
					     va_list args)
{
  ScriptComponent *scriptComp =
    static_cast<ScriptComponent*>(entityManager.getComponent(entityId,
							     ScriptComponent::name));
  std::cout << "making monster spawn script" << std::endl;
  scriptComp->setScript(new MonsterSpawnScript(entityManager));
}
