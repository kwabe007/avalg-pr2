#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include "algo.hpp"

int main() {
  int i = 0;
  long l = 0L;
  long long ll = 0LL;
  boost::multiprecision::int128_t int128 = 0;
  unsigned  __int128 i128 = 0;
  std::cout << sizeof(i) << std::endl;
  std::cout << sizeof(l) << std::endl;
  std::cout << sizeof(ll) << std::endl;
  std::cout << sizeof(int128) << std::endl;
  std::cout << sizeof(i128) << std::endl;
  //std::cout << i128 << std::endl;

  std::list<unsigned long long> queue = fermats(548LL);

  for (unsigned long long i : queue) {
    std::cout << i << std::endl;
  }
  
  
  return 0;
}
