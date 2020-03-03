#ifndef _OW_NETWORK_HPP_
#define _OW_NETWORK_HPP_

#ifdef _WIN32
# ifdef OW_NETWORK_EXPORTS
#   define OW_API __declspec(dllexport)
# else
#   define OW_API __declspec(dllimport)
# endif
#else // linux
# ifdef OW_NETWOR_EXPORTS
#   define OW_API __attribute__((visibility("default")))
# else
#   define OW_API
# endif
#endif

namespace ow
{

class OW_API analyzer_webserver
{
public:
  analyzer_webserver();
  ~analyzer_webserver();

  void run();
  void stop();

private:
  class implement;
  implement* impl;
};

} // namespace ow

#endif // _OW_NETWORK_HPP_
