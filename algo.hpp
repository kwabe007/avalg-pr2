#include <gmp.h>
#include <ctime>
#include "tools.hpp"

#ifndef ALGO_HPP
#define ALGO_HPP


std::clock_t MAX_CLOCK_FERMATS = 10000LL;

//helper-function to check whether an integer 'a' (> 0) is a square of another integer 'b'
//If true it returns the integer 'b' otherwise it returns 0

void is_square(mpz_t& result, const mpz_t& n){
  mpz_t root_n, root_n_squared;
  mpz_init2(root_n, 100);
  mpz_init2(root_n_squared, 100);
  
  mpz_sqrt(root_n, n); 
  mpz_pow_ui(root_n_squared, root_n, 2);

  if(mpz_cmp(root_n_squared, n) == 0){
    mpz_set(result, root_n);
  }
  else {
    mpz_set_ui(result, 0);
  }
  
  mpz_clears(root_n, root_n_squared, NULL);

}

//function for prime factorization using fermats factorization method
bool fermats(struct linked_list* result, const mpz_t& n) {
  std::clock_t begin = std::clock();
  struct linked_list queue;
  mpz_t current_number, current_number_div2, sqr_number, pow_of_sqr_number, sum, integer_square_sum, root_sum, factor1, factor2;
  bool status = 1;

  queue.add(n);
  mpz_init2(current_number, 100);
  mpz_init2(current_number_div2, 100);
  mpz_init2(sqr_number,100);
  mpz_init2(pow_of_sqr_number, 100);
  mpz_init2(sum, 100);
  mpz_init2(integer_square_sum, 100);
  mpz_init2(root_sum, 100);
  mpz_init2(factor1, 100);
  mpz_init2(factor2, 100);

  while (!queue.is_empty()) {
    queue.pop(current_number);
    bool is_prime = true;
  
    //Check if the current number is even (excluding 2)
    if (mpz_even_p(current_number) && mpz_cmp_ui(current_number, 2)!= 0) {
      if (!queue.add(2)) {
	status = 0;
	goto cleanup;
      }
      mpz_fdiv_q_ui(current_number_div2, current_number, 2);
      if(!queue.add(current_number_div2)) {
	status = 0;
	goto cleanup;
      }
      continue;
    }
 

    for (mpz_set_ui(sqr_number, 0); mpz_cmp(sqr_number, current_number) < 0 ; mpz_add_ui(sqr_number, sqr_number, 1) ) {
    
      mpz_pow_ui(pow_of_sqr_number, sqr_number, 2);
      mpz_add(sum ,current_number, pow_of_sqr_number);
      is_square(root_sum, sum);

      if ((std::clock() - begin) > MAX_CLOCK_FERMATS) {
	status = 0;
	goto cleanup;
      }
    
      if (mpz_cmp_ui(root_sum, 0) > 0) {
	  
	mpz_sub(factor1, root_sum, sqr_number);
	mpz_add(factor2, root_sum, sqr_number);
      
	if (mpz_cmp_ui(factor1, 1) == 0 || mpz_cmp_ui(factor2, 1) == 0)	 
	  break;
	  
	if (!queue.add(factor1)){
	  status = 0;
	  goto cleanup;
	}
	if (!queue.add(factor2)){
	  status = 0;
	  goto cleanup;
	}
	is_prime = false;
	break;
      }

      
    }
  
    if (is_prime) {
      result->add(current_number);
    }
              
  }
  
 cleanup: //free allocated memory for mpz-variables
  mpz_clears(current_number, current_number_div2, sqr_number, pow_of_sqr_number, sum, integer_square_sum, root_sum, factor1, factor2, NULL);

  return status;
}

#endif
