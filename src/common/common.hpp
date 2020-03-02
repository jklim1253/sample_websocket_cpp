#ifndef _COMMON_HPP_
#define _COMMON_HPP_

namespace ow
{

struct elapsed_time
{
  elapsed_time(const char* _tag);
  ~elapsed_time();

private :
  struct implement;
  implement* impl;
};

} // namespace ow

#endif // _COMMON_HPP_
