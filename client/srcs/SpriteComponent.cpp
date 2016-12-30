
#include       "SpriteComponent.hpp"

const std::string SpriteComponent::name = "SpriteComponent";

SpriteComponent::SpriteComponent() : _isAnimated(false),
                                     _isFullFrames(false),
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

bool                            SpriteComponent::isFullFrames(void) const
{
  return _isFullFrames;
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

void                            SpriteComponent::setFrames(const std::vector<unsigned int> &frames,
                                                           const unsigned int nbFrames)
{
  for (auto it : frames)
    _frames.push_back(it);
  _nbFrames = nbFrames;
}

void                            SpriteComponent::setFrames(const std::vector<std::vector<unsigned int> > &fullFrames)
{
  for (auto it : fullFrames)
    _fullFrames.push_back(it);
  _isFullFrames = true;
}

const std::vector<unsigned int>& SpriteComponent::getFrames(void) const
{
  return _frames;
}

const std::vector<std::vector<unsigned int> >& SpriteComponent::getFullFrames(void) const
{
  return _fullFrames;
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
