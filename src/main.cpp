#include <iostream>
#include "common/common.hpp"
#include "network/network.hpp"

int main(int argc, char* argv[])
{
  std::cout << "hello world" << std::endl;

  {
    ow::analyzer_webserver service;
    service.run();
  }

  return 0;
}