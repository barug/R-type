//
// mSFML
//

# include	"Timer.hpp"

Timer::Timer() : _timerState(NONE)
{
}

Timer::~Timer()
{
}

void                    Timer::reset()
{
  _timerState = Timer::State::NONE;
}

void			Timer::setState(const Timer::State& timerState)
{
  _timerState = timerState;
}

const Timer::State&	Timer::getState() const
{
  return (_timerState);
}

unsigned int		Timer::timeLeft()
{
  return (std::chrono::duration_cast<std::chrono::milliseconds>(_now - _then).count());
}

bool			Timer::timerIn(const unsigned int timer)
{
  if (_timerState == Timer::State::TIMER_OUT)
    return (false);
  if (_timerState == Timer::State::NONE)
    _then = std::chrono::system_clock::now();
  _now = std::chrono::system_clock::now();
  if (std::chrono::duration_cast<std::chrono::milliseconds>(_now - _then).count() > timer)
    {
      _then = _now;
      _timerState = Timer::State::TIMER_OUT;
      return (false);
    }
  else
    {
      _timerState = Timer::State::TIMER_IN;
      return (true);
    }
}
