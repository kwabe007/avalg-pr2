#include <gmp.h>
#include "tools.hpp"

#ifndef ALGO_HPP
#define ALGO_HPP

using namespace boost::multiprecision;

//helper-function to check whether an integer 'a' (> 0) is a square of another integer 'b'
//If true it returns the integer 'b' otherwise it returns 0

void is_square(mpz_t& result, const mpz_t& n){
  mpz_t root_n;
  mpz_init2(root_n, 100);
  mpz_sqrt(root_n, n);
  
  mpz_t root_n_squared;
  mpz_init2(root_n_squared, 100);
  mpz_pow_ui(root_n_squared, root_n, 2);

  if(mpz_cmp(root_n_squared, n) == 0){
      mpz_set(result, root_n);
      return;
  }
  else {
    mpz_set_ui(result, 0);
    return ;
  }

}

//function for prime factorization using fermats factorization method
struct linked_list* fermats(struct linked_list* result, const mpz_t& n) {
  struct linked_list queue;
  mpz_t current_number; 
  queue.add(n);
  mpz_init2(current_number, 100);

  while (!queue.is_empty()) {
    queue.pop(current_number);
    bool is_prime = true;
  
    //Check if the current number is even (excluding 2)
    if (mpz_even_p(current_number) && mpz_cmp_ui(current_number, 2)!= 0) {
      queue.add(2);
      mpz_t current_number_div2;
      mpz_init2(current_number_div2, 100);
      mpz_fdiv_q_ui(current_number_div2, current_number, 2);
      queue.add(current_number_div2);
      continue;
    }
  
    mpz_t sqr_number;
      
    for (mpz_init_set_ui(sqr_number, 0); mpz_cmp(sqr_number, current_number) < 0 ; mpz_add_ui(sqr_number, sqr_number, 1) ) {
	mpz_t pow_of_sqr_number, sum, integer_square_sum, root_sum;
	mpz_init2(pow_of_sqr_number, 100);
	mpz_init2(sum, 100);
	mpz_init2(integer_square_sum, 100);
	mpz_init2(root_sum, 100);
    
	mpz_pow_ui(pow_of_sqr_number, sqr_number, 2);
	mpz_add(sum ,current_number, pow_of_sqr_number);
	is_square(root_sum, sum);
    
	if (mpz_cmp_ui(root_sum, 0) > 0) {
	  mpz_t factor1, factor2;
	  mpz_init2(factor1, 100);
	  mpz_init2(factor2, 100);
	  
	  mpz_sub(factor1, root_sum, sqr_number);
	  mpz_add(factor2, root_sum, sqr_number);
      
	  if (mpz_cmp_ui(factor1, 1) == 0 || mpz_cmp_ui(factor2, 1) == 0)
	    break;
      
	  queue.add(factor1);
	  queue.add(factor2);
	  is_prime = false;
	  break;
	}
    
      }
  
      if (is_prime) {
	result->add(current_number);
      }
              
      }

    return result;
  }

#endif
