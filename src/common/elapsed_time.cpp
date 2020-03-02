#include "common/common.hpp"

#include <iostream>
#include <string>
#include <chrono>

namespace ow
{

struct elapsed_time::implement
{
  std::string m_tag;
  std::chrono::steady_clock::time_point m_st;

  implement(const char* _tag)
    : m_tag(_tag)
  {
    m_st = std::chrono::steady_clock::now();
  }
  ~implement()
  {
    auto diff = (std::chrono::steady_clock::now() - m_st);

    std::cout << '[' << m_tag << "] ";
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
    if (sec.count() > 0) {
      std::cout << sec.count() << "s:";
    }
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    if (msec.count() > 0) {
      std::cout << (msec.count()%1000) << "ms:";
    }
    auto usec = std::chrono::duration_cast<std::chrono::microseconds>(diff);
    if (usec.count() > 0) {
      std::cout << (usec.count()%1000) << "us";
    }

    std::cout << " elapsed." << std::endl;
  }
};

elapsed_time::elapsed_time(const char* _tag)
  : impl(new implement(_tag))
{
}
elapsed_time::~elapsed_time()
{
  if (impl)
  {
    delete impl;
    impl = nullptr;
  }
}

} // namespace ow
