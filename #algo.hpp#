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


//Psuedorandom function for pollards algorithm. Generates an integer between [0,n)
//'op' and 'n' are used as arguments. Result is stored in 'res'
void poly(mpz_t& res, const mpz_t& op, const mpz_t& n) {
  mpz_t pow_res, poly_res;
  unsigned int A = 2;
  mpz_init2(pow_res, 100);
  mpz_init2(poly_res, 100);
  
  mpz_pow_ui(pow_res, op, 2);
  mpz_add_ui(poly_res, pow_res, A);
  mpz_fdiv_r(res, poly_res, n);
  
}

bool pollards_read_primes() {
  return 1;
}

//function for factorization using pollards factorization method
bool pollards(struct linked_list* result, const mpz_t& n, unsigned int* prime_ptr) {
  //std::clock_t begin = std::clock();
  struct linked_list queue;
  mpz_t current_number, current_number_div2, q_div_prime, r_div_prime, x1, x2, diff_x1_x2, gcd_res, div_2;
  bool status = 1;
  unsigned int prime_index;
  extern unsigned long MAX_TRIES;
  extern unsigned int MAX_PRIME;
  
  
  queue.add(n);
  mpz_init2(current_number, 100);
  mpz_init2(current_number_div2, 100);
  mpz_init2(q_div_prime, 100);
  mpz_init2(r_div_prime, 100);
  mpz_init2(x1, 100);
  mpz_init2(x2, 100);
  mpz_init2(diff_x1_x2, 100);
  mpz_init2(gcd_res, 100);
  mpz_init2(div_2, 100);

  while(!queue.is_empty()) {
    queue.pop(current_number);
    #ifdef DEBUG
    std::cout << "current number: " << current_number << std::endl;
    #endif
    mpz_set_ui(x1, 1);
    mpz_set_ui(x2, 0);
    prime_index = 0; //holds the index of the prime that is currently pointed at
    unsigned long long count = 0;

    //check if prime, this check gives correct positives but can give false negatives
    int prime_status = mpz_probab_prime_p(current_number, 40);
    if (prime_status == 2){ 
      result->add(current_number);
      continue;
    }

    //otherwise we assume it is composite and try to crack the number
    //This works with two methods, one is by by 'brute force' dividing by primes and the other is by pollards method 
    while(true) {

      //fail condition: too many tries
      if (count > MAX_TRIES) {
	goto fail;
      }


      //method 1: 'brute-force' prime-division
      //check if its divisble by some primes from a lookup
      //the amount of primes it can check is limited by MAX_PRIME
      if (prime_index < MAX_PRIME) {
	unsigned int prime = prime_ptr[prime_index];
	mpz_fdiv_qr_ui(q_div_prime, r_div_prime, current_number, prime);
	if(mpz_cmp_ui(r_div_prime, 0) == 0) {
	  queue.add(prime);
	  queue.add(q_div_prime);
	  break;
	} else {
	  ++prime_index; //if the prime was not a divisor to the current number, set index to the next prime
	}
      }

      //method 2: pollards method
      //if x1 and x2 are equal we have found a loop so no point in using the same polynomial function
      if (mpz_cmp(x1,x2)) {
	mpz_sub(diff_x1_x2, x1, x2);
	mpz_abs(diff_x1_x2, diff_x1_x2);
	mpz_gcd(gcd_res, diff_x1_x2, current_number);
    
	if(mpz_cmp_ui(gcd_res, 1) > 0) {
	  queue.add(gcd_res);
	  mpz_fdiv_q(div_2, current_number, gcd_res);
	  queue.add(div_2);
	  #ifdef DEBUG
	  std::cout << "added: " << gcd_res << ", " << div_2 <<  std::endl;
	  #endif
	  break;
	}
	poly(x1, x1, current_number);
	poly(x2, x2, current_number);
	poly(x2, x2, current_number);
      }

      ++count;
    
    }
    
  }
  
  goto clean_pollard;

 fail: //mark fail
  status = 0;

 clean_pollard: //free allocated memory for mpz-variables
  mpz_clears(current_number, current_number_div2, q_div_prime, r_div_prime, x1, x2, diff_x1_x2, gcd_res, div_2, NULL);
  return status;
    
}

#endif
