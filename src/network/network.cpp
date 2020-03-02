#include "network/network.hpp"
#include <websocketpp/client.h>

namespace ow
{

signaling::signaling()
{

}
signaling::~signaling()
{

}

void signaling::sendOffer()
{

}
void signaling::sendICECandidate()
{

}

#if defined(_DEBUG) || defined(DEBUG)
void signaling::test()
{
  elapsed_time check("signaling test");

  websocket::client cli;
}
#endif

} // namespace ow
