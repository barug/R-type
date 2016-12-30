#ifndef         __SPRITE_COMPONENT_HPP_
# define        __SPRITE_COMPONENT_HPP_

# include       <vector>
# include       "IComponent.hpp"
# include       "AnimatedSprite.hpp"

class           SpriteComponent : public IComponent
{
  bool                          _isAnimated;
  bool                          _isFullFrames;
  unsigned int                  _nbFrames;
  std::string			_path;
  std::string                   _entityName;
  std::vector<unsigned int>     _frames;
  std::vector<std::vector<unsigned int> > _fullFrames;
  AnimatedSprite                *_animatedSprite;
  Animation                     _animation;

public:
  static const std::string	name;
  SpriteComponent();
  virtual ~SpriteComponent();
  virtual const std::string     getName(void);

  const std::string             &getPath(void) const;
  void				setPath(const std::string &path);
  bool                          isFullFrames(void) const;
  bool                          isAnimated(void) const;
  void				setPathAnimated(const std::string &path);
  void                          setEntityName(const std::string &entityName);
  const std::string             &getEntityName(void) const;
  const unsigned int            getHeight(void) const;
  const unsigned int            getWidth(void) const;

  // rect assimilation
  void                          setFrames(const std::vector<unsigned int> &rec, const unsigned int nbFrames);
  void                          setFrames(const std::vector<std::vector<unsigned int> > &allRec);
  const std::vector<unsigned int> &getFrames(void) const;
  const std::vector<std::vector<unsigned int> > &getFullFrames(void) const;
  const unsigned int            getNbFrames(void) const;

  // animationToolSet
  void                          setAnimation(const Animation &animation);
  void                          setAnimationSpeedLoop(const float speedLoop);
  const Animation&              getAnimation(void) const;
  AnimatedSprite*               getAnimatedSprite(void) const;

};

#endif          // !__SPRITE_COMPONENT_HPP_
