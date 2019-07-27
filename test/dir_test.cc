#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include <iostream>

namespace pecomp
{
namespace
{
  TEST(dir, one)
  {
    using namespace boost::filesystem;

    int file_counter = 0;
    for(directory_iterator itr("test/algorithms"); itr != directory_iterator(); ++itr)
    {
      if(is_regular_file(itr->status()))
      {
        // std::cout << " [" << file_size(itr->path()) << ']' << std::endl;
        ++file_counter;
      }
    }
    ASSERT_GE(file_counter, 1);
  }
} // namespace
} // namespace pecomp
