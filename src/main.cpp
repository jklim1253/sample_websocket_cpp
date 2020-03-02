#include <iostream>
#include "common/common.hpp"
#include "network/network.hpp"

int main(int argc, char* argv[])
{
  std::cout << "hello world" << std::endl;

#if defined(_DEBUG) || defined(DEBUG)
  {
    ow::signaling serv;
    serv.test();
  }
#endif

  return 0;
}