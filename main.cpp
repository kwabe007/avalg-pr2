#include <gmp.h>
#include <iostream>
#include "algo.hpp"
#include "tools.hpp"

unsigned long MAX_TRIES = 190000L;
unsigned int PRIME_ARRAY[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541};
unsigned int PRIMES_TO_TRY = 100; //The first n primes to try in prime_array for the prime division, NOTE: Must be smaller than size of prime_array or undefined behaviour

int main() {

  
  mpz_t n, res;
  mpz_init2(n, 100);
  mpz_init2(res, 100);
  struct linked_list result;

  while(mpz_inp_str(n, stdin, 10)) {

    if(pollards(&result, n)) { 
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
