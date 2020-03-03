#include "network/network.hpp"
#include "common/common.hpp"

#include <list>

#pragma warning(disable:4267)
#include <websocketpp/client.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/message_buffer/message.hpp>
#pragma warning(default:4267)

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

namespace ow
{

typedef websocketpp::client<websocketpp::config::asio_client> client_t;
typedef websocketpp::server<websocketpp::config::asio> server_t;

class analyzer_webserver::implement
{
  server_t m_server;

  server_t::connection_ptr m_connection;

public:
  implement()
    : m_connection(nullptr)
  {
    m_server.init_asio();
  }
  ~implement()
  {

  }
  void run()
  {
    elapsed_time check("analyzer_webserver run");

    // handlers
    m_server.set_open_handler([=](websocketpp::connection_hdl conn){
      on_open(conn);
    });
    m_server.set_fail_handler([=](websocketpp::connection_hdl conn){
      on_fail(conn);
    });
    m_server.set_message_handler([=](websocketpp::connection_hdl conn, server_t::message_ptr msg){
      on_message(conn, msg);
    });
    m_server.set_http_handler([=](websocketpp::connection_hdl conn){
      on_http(conn);
    });

    // run
    m_server.listen(8888);

    m_server.start_accept();

    m_server.run();
  }
  void stop()
  {
    m_server.stop();

    m_connection = nullptr;
  }
private:
  void on_open(websocketpp::connection_hdl conn)
  {
    std::cout << "opened" << std::endl;

    if (m_connection == nullptr)
    {
      m_connection = m_server.get_con_from_hdl(conn);
      std::cout << "remote: " << m_connection->get_remote_endpoint() << std::endl;
    }
  }
  void on_fail(websocketpp::connection_hdl conn)
  {
    std::cout << "failed" << std::endl;
  }
  void on_message(websocketpp::connection_hdl conn, server_t::message_ptr msg)
  {
    auto conn_ptr = m_server.get_con_from_hdl(conn);
    std::cout << "remote: " << conn_ptr->get_host() << ':' << conn_ptr->get_port() << std::endl;
    // std::cout << "header: " << msg->get_header() << std::endl;
    // std::cout << "content: " << msg->get_payload() << std::endl;

    parse(msg->get_payload());
  }
  void on_http(websocketpp::connection_hdl conn)
  {
    auto conn_ptr = m_server.get_con_from_hdl(conn);
    // TODO: http not supported response
  }
  void parse(std::string const& json)
  {
    std::cout << "parse " << std::endl;
    rapidjson::Document document;
    document.Parse(json.c_str());
    std::cout << "parsed" << std::endl;

    if (document.GetParseError() != rapidjson::ParseErrorCode::kParseErrorNone)
    {
      std::cout << "error: " << document.GetParseError() << std::endl;
      return;
    }

    auto value = document.FindMember("utf8Data");
    if (value != document.MemberEnd())
    {
      std::cout << "utf8Data: " << value->value.GetType() << std::endl;
      if (value->value.IsString())
      {
        std::cout << "utf8Data: " << value->value.GetString() << std::endl;
      }
    }

    if (false && value->value.IsString())
    {
      std::cout << "sub document parse" << std::endl;
      rapidjson::Document subdoc;
      std::string sub_json(value->value.GetString());
      subdoc.Parse(sub_json.c_str());
      std::cout << "sub document parsed" << std::endl;

      value = subdoc.FindMember("data");
      if (value != subdoc.MemberEnd())
      {
        std::cout << "data: " << value->value.GetType() << std::endl;
        if (value->value.IsString())
        {
          std::cout << "data: " << value->value.GetString() << std::endl;
        }
      }

      value = subdoc.FindMember("sdp");
      if (value != subdoc.MemberEnd())
      {
        std::cout << "sdp: " << value->value.GetType() << std::endl;
        if (value->value.IsString())
        {
          std::cout << "sdp: " << value->value.GetString() << std::endl;
        }
      }
    }
  }
};

analyzer_webserver::analyzer_webserver()
  : impl(new implement())
{
}
analyzer_webserver::~analyzer_webserver()
{
  if (impl)
  {
    delete impl;
    impl = nullptr;
  }
}
void analyzer_webserver::run()
{
  impl->run();
}
void analyzer_webserver::stop()
{
  impl->stop();
}

} // namespace ow
