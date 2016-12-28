//
// made by kama 13/12/2016
// thomas.bogard@epitech.eu
//

#ifndef				__IDYNAMIC_LOADER_HPP__
# define			__IDYNAMIC_LOADER_HPP__

# include			<map>
# include			<string>

class				IDynamicLoader
{
public:
  typedef void (*ptrToF)(EntityManager &, SystemManager&, MessageBus &);
  typedef ptrToF	(*f)();

  virtual ~IDynamicLoader() {}
  virtual ptrToF                load(const std::string &libName, const std::string &symName) = 0;
  virtual void			close(const std::string &symName) = 0;
};

#if defined(__GNUC__)
# include			<dlfcn.h>
class				unixDynamicLoader : public IDynamicLoader
{
public:
  unixDynamicLoader() {}
  virtual ~unixDynamicLoader() {
    for (auto it : _hashHandler)
      close(it.first);
  }

  virtual ptrToF                load(const std::string &libName, const std::string &symName)
  {
    f                           fPtr;
    std::string			newLibName = libName;
    void			*handler = dlopen(newLibName.c_str(), RTLD_LAZY);

    _hashHandler[symName] = handler;
    if (!(fPtr = reinterpret_cast<f>(dlsym(handler, symName.c_str()))))
      {
	std::cerr << "[DynamicLoader::Load] failure : " << dlerror() << std::endl;
      }
    return fPtr();
  }

  virtual void			close(const std::string &symName)
  {
    dlclose(_hashHandler[symName]);
    _hashHandler.erase(symName);
  }

private:
  std::map<std::string, void *> _hashHandler;

};
# elif		defined(_WIN32) || defined(WIN32)
# include			<windows.h>
class				windowsDynamicLoader : public IDynamicLoader
{
public:
  windowsDynamicLoader() {}
  virtual ~windowsDynamicLoader() {
    for (auto it : _hashHandler)
      close(it.first);
  }
#include <string>
  virtual ptrToF        	load(const std::string &libName, const std::string &symName)
  {
    f           		fPtr;
    std::string			newLibName = libName + ".dll";
    void			*handler = (void*)LoadLibrary((newLibName.c_str()));

    _hashHandler[symName] = handler;
    if (!(fPtr = reinterpret_cast<f>(GetProcAddress((HINSTANCE)handler, symName.c_str()))))
      {
        std::cerr << "[DynamicLoader::Load] failure : " << std::endl;
      }
    return fPtr();
  }

  virtual void			close(const std::string &symName)
  {
    FreeLibrary((HINSTANCE)_hashHandler[symName]);
    _hashHandler.erase(symName);
  }

private:
  std::map<std::string, void *> _hashHandler;

};

#endif

#endif				// !__IDYNAMIC_LOADER_HPP__
