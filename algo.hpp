#include <gmp.h>
#include <tools>

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
mpz_t sqr_number;


while (!queue.empty()) {
  mpz_t current_number = queue.front();
  queue.pop_front();
  bool is_prime = true;
  
  if (!(current_number & 1LL) && current_number != 2LL) {
    queue.push_back(2LL);
    queue.push_back(current_number/2);
    continue;
    
  }
  
  for (sqr_number = 1; sqr_number < current_number; ++sqr_number ) {
    mpz_t pow_of_sqr_number, sum, integer_square_sum;
    mpz_init2(pow_of_sqr_number);
    mpz_init2(sum);
    mpz_init2(integer_square_sum);
    
    mpz_pow_ui(pow_of_sqr_number, sqr_number, 2);
    mpz_add(sum ,current_number, pow_of_sqr_number)
    integer_square_sum = is_square(sum);
    
    if (integer_square_sum > 0LL) {
      mpz_t factor1 = integer_square_sum - sqr_number;
      mpz_t factor2 = integer_square_sum + sqr_number;
      
      if (factor1 == 1LL || factor2 == 1LL)
	break;
      
      queue.push_back(factor1);
      queue.push_back(factor2);
      is_prime = false;
      break;
    }
    
  }
  
  if (is_prime) {
    result.push_back(current_number);
  }
              
 }

return result;
}

#endif
