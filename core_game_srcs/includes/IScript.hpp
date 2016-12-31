
#ifndef _ISCRIPT_HPP_
# define _ISCRIPT_HPP_



class			IScript
{
public:
  virtual ~IScript() {}
  virtual void		operator()() = 0;
};

#endif /* !_ISCRIPT_HPP_ */
