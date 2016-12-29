
#include       "SpriteComponent.hpp"

const std::string SpriteComponent::name = "SpriteComponent";

SpriteComponent::SpriteComponent() : _isAnimated(false),
                                     _allRecActivated(false),
                                     _animatedSprite(NULL)
{}

SpriteComponent::~SpriteComponent()
{
  if (_animatedSprite)
    delete _animatedSprite;
}

const std::string               SpriteComponent::getName(void)
{
  return SpriteComponent::name;
}

const std::string&              SpriteComponent::getPath(void) const
{
  return _path;
}

void				SpriteComponent::setPath(const std::string &path)
{
  _path = path;
}

void                            SpriteComponent::setPathAnimated(const std::string &path)
{
  _path = path;
  _isAnimated = true;
  if (!_animatedSprite)
    _animatedSprite = new AnimatedSprite;
}

bool                            SpriteComponent::isAnimated(void) const
{
  return _isAnimated;
}

const std::string&              SpriteComponent::getEntityName(void) const
{
  return _entityName;
}

void                            SpriteComponent::setEntityName(const std::string &entityName)
{
  _entityName = entityName;
}

void                            SpriteComponent::setRec(const std::vector<unsigned int> &rec,
                                                        const unsigned int nbFrames)
{
  for (auto it : rec)
    _rec.push_back(it);
  _nbFrames = nbFrames;
}

void                            SpriteComponent::setAllRec(const std::vector<std::vector<unsigned int> > &allRec,
                                                           const unsigned int nbFrames)
{
  for (auto it : allRec)
    _allRec.push_back(it);
  _nbFrames = nbFrames;
  _allRecActivated = true;
}

const std::vector<unsigned int>& SpriteComponent::getRec(void) const
{
  return _rec;
}

const std::vector<std::vector<unsigned int> >& SpriteComponent::getAllRec(void) const
{
  return _allRec;
}

const unsigned int              SpriteComponent::getNbFrames(void) const
{
  return _nbFrames;
}

void                            SpriteComponent::setAnimation(const Animation &animation)
{
  _animation = animation;
}

void                            SpriteComponent::setAnimationSpeedLoop(const float speedLoop)
{
  if (_animatedSprite)
    _animatedSprite->setFrameTime(speedLoop);
}

AnimatedSprite*                 SpriteComponent::getAnimatedSprite(void) const
{
  return _animatedSprite;
}

const Animation&                SpriteComponent::getAnimation(void) const
{
  return _animation;
}
