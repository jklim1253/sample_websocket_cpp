#include "common/common.hpp"

#include <string>
#include <chrono>

namespace ow
{

using std;
using std::chrono;

struct elapsed_time::implement
{
  typedef elapsed_time parent_t;
  parent_t* m_parent;

  string m_tag;
  steady_clock::time_point m_st;

  implement(parent_t* _parent, string const& _tag)
    : m_parent(_parent)
    , m_tag(_tag)
  {
    m_st = steady_clock::now();
  }
  ~implement()
  {
    auto diff = steady_clock::now();

    cout << '[' << m_tag << "] ";
    auto sec = duraction_cast<seconds>(diff);
    if (sec.count() > 0) {
      cout << sec.count() << "s:";
    }
    auto msec = duraction_cast<milliseconds>(diff);
    if (msec.count() > 0) {
      cout << msec.count() << "ms:";
    }
    auto usec = duraction_cast<microseconds>(diff);
    if (usec.count() > 0) {
      cout << usec.count() << "us";
    }

    cout << " elapsed." << endl;
  }
};

elapsed_time::elapsed_time(const char* _tag)
  : impl(new implement(this, _tag))
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
