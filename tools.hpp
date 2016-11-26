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

  void add(const mpz_t& new_val) {
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
  }
  
  void add(unsigned new_val_ui) {
    mpz_t new_val;
    mpz_init_set_ui(new_val, new_val_ui);
    add(new_val);
    mpz_clear(new_val);
  }

  void pop(mpz_t& result) {
    if (start) {
      mpz_set(result, start->val);

      struct node* new_start = start->next;
      mpz_clear(start->val);
      delete start;
      start = new_start;
    }
  }

  bool is_empty() {
    return start == nullptr;
  }
  
};


#endif
