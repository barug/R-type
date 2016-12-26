//
// mSFML
//

#ifndef		_AUDIO_HPP_
# define	_AUDIO_HPP_

# include	<SFML/Audio.hpp>
# include	"IAudio.hpp"

class		Audio : public IAudio
{
public:
  Audio();
  virtual ~Audio();

  virtual void		loadSound(const std::string &path);
  virtual void		loadMusic(const std::string &path);

  virtual void		musicPlay();
  virtual void		musicPause();
  virtual void		musicStop();
  virtual void		musicSetVolume(const unsigned int volume);
  virtual void		musicSetLoop(const bool isLoop);

  virtual void		soundPlay();
  virtual void		soundSetVolume(const unsigned int volume);
  virtual void		soundSetLoop(const bool isLoop);

protected:
  sf::SoundBuffer	_buffer;
  sf::Sound		_sound;
  sf::Music		_music;
};

#endif			// _AUDIO_HPP_
