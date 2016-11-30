#ifndef TOOLSHPP
#define TOOLSHPP

#include<gmp.h>

struct node {
  mpz_t val;
  struct node *next = nullptr;
};

struct linked_list {
  struct node *start = nullptr;
  struct node *end = nullptr;
  unsigned long long limit = -1;
  unsigned size = 0;

  bool add(const mpz_t& new_val) {
    if(size == limit)
      return 0;
    if (!start) {
      start = new struct node;
      mpz_init_set(start->val, new_val);
      end = start;
    } else {
      struct node* new_end = new struct node;
      mpz_init_set(new_end->val, new_val);
      end->next = new_end;
      end = new_end;
    }
    ++size;
    return 1;
  }
  
  
  bool add(unsigned new_val_ui) {
    mpz_t new_val;
    mpz_init_set_ui(new_val, new_val_ui);
    bool result = add(new_val);
    mpz_clear(new_val);
    return result;
  }

  void pop(mpz_t& result) {
    if (start) {
      mpz_set(result, start->val);

      struct node* new_start = start->next;
      mpz_clear(start->val);
      delete start;
      start = new_start;
    }
    --size;
  }

  bool is_empty() {
    return start == nullptr;
  }
  
};

//Generate primes
void write_primes_txt(const char* source) {
  
  FILE *file_in;
  if ((file_in = fopen(source, "r")) ==NULL){
    printf("Error opening file\n");
    exit(1);
  }

  FILE *file_out;
  if ((file_out = fopen("prime-comma", "w")) ==NULL){
    printf("Error opening file\n");
    exit(1);
  }

#ifdef DEBUG
  unsigned int first;
  unsigned int last;
#endif
  unsigned int val;
  unsigned long int count = 0;
  for(count = 0; fscanf(file_in, "%d",&val) != EOF; ++count) {
#ifdef DEBUG
    if (count == 0)
      first = val;
    last = val;
#endif
    fprintf(file_out, "%u, ", val);
  }

#ifdef DEBUG
  printf("wrote %lu primes, first: %u, last: %u\n", count, first, last);
#endif
    
}
void write_primes(const char* source) {
  
  FILE *file_in;
  if ((file_in = fopen(source, "r")) ==NULL){
    printf("Error opening file\n");
    exit(1);
  }

  FILE *file_out;
  if ((file_out = fopen("primes", "wb")) ==NULL){
    printf("Error opening file\n");
    exit(1);
  }

  unsigned int val;
  unsigned long int count = 0;
  while(fscanf(file_in, "%d",&val) != EOF) {   
    fwrite(&val, sizeof(val), 1, file_out);
    ++count;
  }

  std::cerr << "read " << count << " primes" << std::endl;

  FILE *file_read;
  if ((file_read = fopen("primes", "rb")) ==NULL){
    printf("Error opening file\n");
    exit(1);
  }

  unsigned int r_val;
  while(fread(&r_val, sizeof(val), 1, file_read)) {
    //printf("%d",val);
    //putchar('\n');
    }
    
}

//reads the first x primes and store them in an array
  unsigned int* read_primes(unsigned int size){
    FILE* file_in;
    
    if ((file_in = fopen("primes", "rb")) ==NULL){
    printf("Error opening file\n");
    exit(1);
  }
    
    unsigned int r_val;
    unsigned int* prime_ptr;
    prime_ptr = new unsigned int [size];
    
    for(unsigned int i = 0; i < size ; ++i) {
      fread(&r_val, sizeof(r_val), 1, file_in);
      prime_ptr[i] = r_val;
    }

    return prime_ptr;
  }

//reads the first x primes and store them in an array
  unsigned int* read_primes_txt(unsigned int size){
    FILE* file_in;
    
    if ((file_in = fopen("primes.hpp", "r")) ==NULL){
    printf("Error opening file\n");
    exit(1);
  }
    
    unsigned int r_val;
    unsigned int* prime_ptr;
    prime_ptr = new unsigned int [size];
    
    for(unsigned int i = 0; i < size ; ++i) {
      fscanf(file_in, "%u", &r_val);
      prime_ptr[i] = r_val;
      #ifdef DEBUG
      std::cerr << "read prime: " << r_val << std::endl;
      #endif
    }
    fclose(file_in);
    return prime_ptr;
  }

#endif
