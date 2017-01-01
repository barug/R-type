
#ifndef _ENTITY_INITIALISER_HPP_
# define _ENTITY_INITIALISER_HPP_

#include "EntityManager.hpp"
#include "PlayerInputSystem.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "HitBoxComponent.hpp"
#include "HealthComponent.hpp"
#include "ScriptComponent.hpp"
#include "BasicMonsterScript.hpp"
#include "MonsterSpawnScript.hpp"
#include <iostream>

void		initializePlayerShip(EntityManager &entityManager,
				     int entityId,
				     va_list args);
void		initializeBasicMonster(EntityManager &entityManager,
				       int entityId,
				       va_list args);

void		initializeBasicProjectile(EntityManager &entityManager,
					  int entityId,
					  va_list args);

void		initializeMonsterSpawnScript(EntityManager &entityManager,
					     int entityId,
					     va_list args);
#endif /* !_ENTITY_INITIALISER_HPP_ */
