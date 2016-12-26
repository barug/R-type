//
// mSFML
//

#include        "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(const float frameTime, const bool paused, const bool looped)
  : _animation(NULL),
    _frameTime(sf::Time(sf::seconds(frameTime))),
    _currentFrame(0),
    _isPaused(paused),
    _isLooped(looped),
    _texture(NULL)
{

}

void            AnimatedSprite::setAnimation(const Animation& animation)
{
    _animation = &animation;
    _texture = _animation->getSpriteSheet();
    _currentFrame = 0;
    setFrame(_currentFrame);
}

void            AnimatedSprite::setFrameTime(sf::Time time)
{
    _frameTime = time;
}

void            AnimatedSprite::play()
{
    _isPaused = false;
}

void            AnimatedSprite::play(const Animation& animation)
{
  if (getAnimation() != &animation)
    setAnimation(animation);
  play();
}

void            AnimatedSprite::pause()
{
  _isPaused = true;
}

void            AnimatedSprite::stop()
{
  _isPaused = true;
  _currentFrame = 0;
  setFrame(_currentFrame);
}

void            AnimatedSprite::setLooped(bool looped)
{
  _isLooped = looped;
}

void            AnimatedSprite::setColor(const sf::Color& color)
{
  _vertices[0].color = color;
  _vertices[1].color = color;
  _vertices[2].color = color;
  _vertices[3].color = color;
}

const Animation* AnimatedSprite::getAnimation() const
{
  return _animation;
}

sf::FloatRect   AnimatedSprite::getLocalBounds() const
{
  sf::IntRect   rect = _animation->getFrame(_currentFrame);
  return sf::FloatRect(0.f, 0.f,
                       static_cast<float>(std::abs(rect.width)),
                       static_cast<float>(std::abs(rect.height)));
}

sf::FloatRect   AnimatedSprite::getGlobalBounds() const
{
  return getTransform().transformRect(getLocalBounds());
}

bool            AnimatedSprite::isLooped() const
{
  return _isLooped;
}

bool            AnimatedSprite::isPlaying() const
{
  return !_isPaused;
}

sf::Time        AnimatedSprite::getFrameTime() const
{
  return _frameTime;
}

void            AnimatedSprite::setFrame(std::size_t newFrame, bool resetTime)
{
  if (_animation)
    {

      sf::IntRect rect = _animation->getFrame(newFrame);
      const float left = static_cast<float>(rect.left) + 0.0001f;
      const float right = left + static_cast<float>(rect.width);
      const float top = static_cast<float>(rect.top);
      const float bottom = top + static_cast<float>(rect.height);

      _vertices[0].position = sf::Vector2f(0.f, 0.f);
      _vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
      _vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
      _vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

      _vertices[0].texCoords = sf::Vector2f(left, top);
      _vertices[1].texCoords = sf::Vector2f(left, bottom);
      _vertices[2].texCoords = sf::Vector2f(right, bottom);
      _vertices[3].texCoords = sf::Vector2f(right, top);

    }

  if (resetTime)
    _currentTime = sf::Time::Zero;
}

void            AnimatedSprite::update(sf::Time deltaTime)
{
  if (!_isPaused && _animation)
    {
      _currentTime += deltaTime;
      if (_currentTime >= _frameTime)
        {
          _currentTime = sf::microseconds(_currentTime.asMicroseconds() % _frameTime.asMicroseconds());
          if (_currentFrame + 1 < _animation->getSize())
            _currentFrame++;
          else
            {
              _currentFrame = 0;
              if (!_isLooped)
                _isPaused = true;
            }
          setFrame(_currentFrame, false);
        }
    }
}

void            AnimatedSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  if (_animation && _texture)
    {
      states.transform *= getTransform();
      states.texture = _texture;
      target.draw(_vertices, 4, sf::Quads, states);
    }
}
