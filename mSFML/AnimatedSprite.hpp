//
// mSFML
//

#ifndef __ANIMATEDSPRITE_HPP__
#define __ANIMATEDSPRITE_HPP__

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

#include "Animation.hpp"

class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
    explicit            AnimatedSprite(const float frameTime = 0.2,
                                       const bool paused = false,
                                       const bool looped = true);

    void                update(sf::Time deltaTime);
    void                setAnimation(const Animation& animation);
    void                setFrameTime(sf::Time time);
    void                play();
    void                play(const Animation& animation);
    void                pause();
    void                stop();
    void                setLooped(bool looped);
    void                setColor(const sf::Color& color);
    const Animation     *getAnimation() const;
    sf::FloatRect       getLocalBounds() const;
    sf::FloatRect       getGlobalBounds() const;
    bool                isLooped() const;
    bool                isPlaying() const;
    sf::Time            getFrameTime() const;
    void                setFrame(std::size_t newFrame, bool resetTime = true);

private:
    const Animation     *_animation;
    sf::Time            _frameTime;
    sf::Time            _currentTime;
    std::size_t         _currentFrame;
    bool                _isPaused;
    bool                _isLooped;
    const sf::Texture   *_texture;
    sf::Vertex          _vertices[4];
    virtual void        draw(sf::RenderTarget &target, sf::RenderStates states) const;

};

#endif // __ANIMATEDSPRITE_HPP__
