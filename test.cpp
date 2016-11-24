#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/special_functions/pow.hpp>
//#include "algo.hpp"
#include "tools.hpp"
#include <gmp.h>

int main() {

  //TODO:
  //REWRITE ALGO SO THAT IT IS PROPERLY ADJUSTED FOR MPZ_T INSTEAD OF UNSIGNED LONG LONG
  //REWRITE FERMATS SO THAT IT USES CUSTOM LINKED LIST INSTEAD AND GET IT RUNNING


  /*int i = 0;
  long l = 0L;
  long long ll = 0LL;
  boost::multiprecision::int128_t int128 = 0;
  boost::multiprecision::int128_t i128 = 5;*/
  //boost::multiprecision::int128_t res = pow(int128, i128);
  /*std::cout << sizeof(i) << std::endl;
  std::cout << sizeof(l) << std::endl;
  std::cout << sizeof(ll) << std::endl;
  std::cout << sizeof(int128) << std::endl;
  std::cout << sizeof(i128) << std::endl;*/

  //Test is_square function
  /*  mpz_t t_sqr1, t_sqr2, t_sqr3, t_sqr4;
  mpz_init_set_ui(t_sqr1, 9);
  mpz_init_set_ui(t_sqr2, 24253);
  mpz_init_set_ui(t_sqr3, 10000);
  mpz_init_set_ui(t_sqr4, 24163);

  mpz_t res1, res2, res3, res4;
  mpz_init_set_ui(res1, 0);
  mpz_init_set_ui(res2, 0);
  mpz_init_set_ui(res3, 0);
  mpz_init_set_ui(res4, 0);

  is_square(res1, t_sqr1);
  is_square(res2, t_sqr2);
  is_square(res3, t_sqr3);
  is_square(res4, t_sqr4);
  
  std::cout << res1 << std::endl;
  std::cout << res2 << std::endl;
  std::cout << res3 << std::endl;
  std::cout << res4 << std::endl;*/

  //linked list test

  mpz_t t_ll1, t_ll2, t_ll3, t_ll4;
  mpz_init_set_ui(t_ll1, 55);
  mpz_init_set_ui(t_ll2, 242);
  mpz_init_set_ui(t_ll3, 100);
  mpz_init_set_ui(t_ll4, 2414263);

  struct linked_list ll;
  
  ll.add(t_ll1);
  ll.add(t_ll2);
  ll.add(t_ll3);
  ll.add(t_ll4);

  mpz_t res;
  mpz_init(res);
  
  while(!ll.is_empty()) {
    ll.pop(res);
    std::cout << res << std::endl;  
  }

  
  
  
  /*mpz_t integ;
  mpz_init2(integ, 100);
  mpz_t integ2;
  mpz_init2(integ2, 100);

  mpz_set_ui(integ2, 5);

  mpz_pow_ui(integ, integ2, 2);

  std::cout << integ << std::endl;*/

  //std::list<mpz_t> queue={0};

  /*for (mpz_t i : queue) {
    std::cout << i << std::endl;
    }*/
  
  
  return 0;
}
