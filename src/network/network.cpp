#include "network/network.hpp"
#include "common/common.hpp"

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_client.hpp>

namespace ow
{

typedef websocketpp::client<websocketpp::config::asio_tls_client> client_t;

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

  client_t cli;
}
#endif

} // namespace ow
