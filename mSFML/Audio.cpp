//
// mSFML
//

# include <iostream>
# include "Audio.hpp"

Audio::Audio()
{}

Audio::~Audio()
{}

void		Audio::loadSound(const std::string &path)
{
  if (this->_sound.getBuffer())
    this->_sound.resetBuffer();
  try
    {
      if (!this->_buffer.loadFromFile(path))
	throw ("[SFML::AUDIO::loadSound] Impossible to load" + path);
    }
  catch (const std::string & error)
    {
      std::cerr << error << std::endl;
    }
  this->_sound.setBuffer(this->_buffer);
}

void	        Audio::loadMusic(const std::string &path)
{
  try
    {
      if (!this->_music.openFromFile(path))
	throw ("[SFML::AUDIO::loadMusic] Impossible to load" + path);
    }
  catch (const std::string & error)
    {
      std::cerr << error << std::endl;
    }
}

void		Audio::musicPlay()
{
  this->_music.play();
}

void	        Audio::musicPause()
{
  this->_music.pause();
}

void		Audio::musicStop()
{
  this->_music.stop();
}

void		Audio::musicSetVolume(const unsigned int volume)
{
  this->_music.setVolume(volume);
}

void		Audio::musicSetLoop(const bool isloop)
{
  this->_music.setLoop(isloop);
}

void		Audio::soundPlay()
{
  this->_sound.play();
}

void		Audio::soundSetVolume(const unsigned int volume)
{
  this->_sound.setVolume(volume);
}

void		Audio::soundSetLoop(const bool isloop)
{
  this->_sound.setLoop(isloop);
}
