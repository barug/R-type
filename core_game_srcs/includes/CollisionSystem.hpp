
#ifndef _COLLISION_SYSTEM_HPP_
# define _COLLISION_SYSTEM_HPP_

# include "ASystem.hpp"
# include "HitBoxComponent.hpp"
# include "PositionComponent.hpp"
# include "coreGameSrcsMessages.hpp"

class			CollisionSystem : public ASystem
{

  std::vector<std::pair<int, int>>	_detectedCollisions;

  bool			testIfAllreadyDetected(int firstId, int secondId);
  
public:

  static const std::string	name;
  
  CollisionSystem(EntityManager &entityManager, MessageBus &messageBus);
  virtual void preRoutine();
  virtual void updateEntity(int entityId);
  virtual void postRoutine();
};

#endif /* !_COLLISION_SYSTEM_HPP_ */
