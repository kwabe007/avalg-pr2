#include <gmp.h>
#include <iostream>
#include "algo.hpp"
#include "tools.hpp"

unsigned long MAX_TRIES = 1000000L;
unsigned int MAX_PRIME = 2;

int main() {

  unsigned int* prime_ptr = read_primes(MAX_PRIME); //read primes from file

  mpz_t n, res;
  mpz_init2(n, 100);
  mpz_init2(res, 100);
  struct linked_list result;

  while(mpz_inp_str(n, stdin, 10)) {

    if(pollards(&result, n, prime_ptr)) { 
      while(!result.is_empty()) {
	result.pop(res);
	mpz_out_str(stdout, 10, res);
	putchar('\n');
      }
    }
    
    else {
      
      puts("fail");
      while(!result.is_empty()) {
	result.pop(res);
      }
      
    }
    putchar('\n');
  }
  
  mpz_clears(n, res, NULL);
}
