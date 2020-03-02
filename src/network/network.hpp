#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

#ifdef _WIN32
# ifdef NETWORK_EXPORTS
#   define NETWORK_API __declspec(dllexport)
# else
#   define NETWORK_API __declspec(dllimport)
# endif
#else // linux
#endif

namespace ow
{

class NETWORK_API signaling
{
public :
  signaling();
  ~signaling();

  void sendOffer();
  void sendICECandidate();

#if defined(_DEBUG) || defined(DEBUG)
  void test();
#endif
};

} // namespace ow

#endif // _NETWORK_HPP_
