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

class OW_API signaling
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

#endif // _OW_NETWORK_HPP_
