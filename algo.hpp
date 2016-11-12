#include <boost/multiprecision/cpp_int.hpp>
#include <list>

#ifndef ALGO_HPP
#define ALGO_HPP

using namespace boost::multiprecision;

unsigned long long is_square(unsigned long long n){
  unsigned long long squareRootN=(unsigned long long)std::round((std::sqrt(n)));

  if(squareRootN*squareRootN == n) {
    return squareRootN;
  }
  else {
    return 0LL;
  }

}

//function for prime factorization using fermats factorization method
std::list<unsigned long long> fermats(unsigned long long n) {
std::list<unsigned long long> queue = {n};
std::list<unsigned long long> result = {};
unsigned long long sqr_number;


while (!queue.empty()) {

  unsigned long long current_number = queue.front();
  queue.pop_front();
  bool is_prime = true;
  
  if (!(current_number & 1LL) && current_number != 2LL) {
    queue.push_back(2LL);
    queue.push_back(current_number/2);
    continue;
    
  }
  
  for (sqr_number = 1; sqr_number < current_number; ++sqr_number ) {
    unsigned long long pow_of_sqr_number = std::pow(sqr_number, 2);
    unsigned long long sum = current_number + pow_of_sqr_number;
    unsigned long long integer_square_sum = is_square(sum);
    
    if (integer_square_sum > 0LL) {
      unsigned long long factor1 = integer_square_sum - sqr_number;
      unsigned long long factor2 = integer_square_sum + sqr_number;
      
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
