
#ifndef _COLLISION_SYSTEM_HPP_
# define _COLLISION_SYSTEM_HPP_

# include "ASystem.hpp"
# include "HitBoxComponent.hpp"
# include "PositionComponent.hpp"

class			CollisionSystem : public ASystem
{

  std::vector<std::pair<int, int>>	_detectedCollisions;

  bool			testIfAllreadyDetected(int firstId, int secondId);
  
public:

  enum			Messages
    {
      COLLISION_DETECTED = 14
    };

  static const std::string	name;
  
  CollisionSystem(EntityManager &entityManager, MessageBus &messageBus);
  virtual void preRoutine();
  virtual void updateEntity(int entityId);
  virtual void postRoutine();
};

#endif /* !_COLLISION_SYSTEM_HPP_ */
