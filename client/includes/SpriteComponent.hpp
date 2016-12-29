#ifndef         __SPRITE_COMPONENT_HPP_
# define        __SPRITE_COMPONENT_HPP_

# include       <vector>
# include       "IComponent.hpp"
# include       "AnimatedSprite.hpp"

class           SpriteComponent : public IComponent
{
  bool                          _isAnimated;
  bool                          _allRecActivated;
  unsigned int                  _nbFrames;
  std::string			_path;
  std::string                   _entityName;
  std::vector<unsigned int>     _rec;
  std::vector<std::vector<unsigned int> > _allRec;
  AnimatedSprite                *_animatedSprite;
  Animation                     _animation;
public:
  static const std::string	name;
  SpriteComponent();
  virtual ~SpriteComponent();
  virtual const std::string     getName(void);

  const std::string             &getPath(void) const;
  void				setPath(const std::string &path);
  bool                          isAnimated(void) const;
  void				setPathAnimated(const std::string &path);
  void                          setEntityName(const std::string &entityName);
  const std::string             &getEntityName(void) const;

  // rect assimilation
  void                          setRec(const std::vector<unsigned int> &rec, const unsigned int nbFrames);
  void                          setAllRec(const std::vector<std::vector<unsigned int> > &allRec,
                                          const unsigned int nbFrames);
  const std::vector<unsigned int> &getRec(void) const;
  const std::vector<std::vector<unsigned int> > &getAllRec(void) const;
  const unsigned int            getNbFrames(void) const;

  // animationToolSet
  void                          setAnimation(const Animation &animation);
  void                          setAnimationSpeedLoop(const float speedLoop);
  const Animation&              getAnimation(void) const;
  AnimatedSprite*               getAnimatedSprite(void) const;

};

#endif          // !__SPRITE_COMPONENT_HPP_
