
#ifndef _HEALTH_SYSTEM_HPP_
# define _HEALTH_SYSTEM_HPP_

class			HealthSystem : public ASystem
{

public:

  static const std::string	name;

  HealthSystem();
  virtual void			preRoutine() {}
  virtual void			updateEntity(int entityId);
  virtual void			postRoutine() {}

  void				handleCollision(void *messageData);
};

#endif /* !_HEALTH_SYSTEM_HPP_ */
