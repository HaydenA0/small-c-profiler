
#include "stdio.h"
#include "time.h"

clock_t start;

void __attribute__((no_instrument_function))
__cyg_profile_func_enter(void *func, void *caller) {
  start = clock();
  printf("ENTER: %p from %p\n", func, caller);
}

void __attribute__((no_instrument_function))
__cyg_profile_func_exit(void *func, void *caller) {
  clock_t end = clock();
  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("EXIT : %p to %p (%f)\n", func, caller, elapsed);
  printf("EXIT : %p to %p\n", func, caller);
}

int functiona(void) { return 0; }

int functionb(void) {
  for (volatile long i = 0; i < 1000000000; i++)
    ;
}

int functionc(void) { return 0; }

int main(void) {

  functiona();
  functionb();
  functionc();

  return 0;
}
