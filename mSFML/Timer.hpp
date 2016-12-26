//
// mSFML
//

#ifndef		_TIMER_HPP_
# define	_TIMER_HPP_

# include	<memory>
# include	<chrono>

class		Timer
{
public:
  Timer();
  ~Timer();

  enum		State
    {
      NONE = 0,
      TIMER_IN = 1,
      TIMER_OUT = 2
    };

  void                                  reset();
  void					setState(const Timer::State& timerState);
  const Timer::State&			getState() const;
  unsigned int				timeLeft();
  bool				        timerIn(const unsigned int timer);

private:
  std::chrono::system_clock::time_point	_now;
  std::chrono::system_clock::time_point _then;
  State					_timerState;
};

#endif		// _TIMER_HPP_
