#include <gmp.h>
#include <iostream>
#include "algo.hpp"
#include "tools.hpp"

int main() {
  mpz_t n, res_fer;
  mpz_init2(n, 100);
  mpz_init2(res_fer, 100);
  struct linked_list result;
  

  while(mpz_inp_str(n, stdin, 10)) {

    if(fermats(&result, n)) { 
      while(!result.is_empty()) {
	result.pop(res_fer);  
	mpz_out_str(stdout, 10, res_fer);
	putchar('\n');
      }
    }
    else {
      puts("fail");
    }
    putchar('\n');

  }
  mpz_clears(n, res_fer, NULL);
}
