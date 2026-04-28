#define _GNU_SOURCE
#include "profiler.h"
#include "timestack.h"
#include <dlfcn.h>
#include <stdio.h>
#include <time.h>

#define no_attribute __attribute__((no_instrument_function))

static TimeStack stack;

void no_attribute print_func_name(void *func) {
  Dl_info info;
  if (dladdr(func, &info) && info.dli_sname) {
    printf("%s", info.dli_sname);
  } else {
    printf("Unknown name, address : %p", func);
  }
}

void no_attribute __cyg_profile_func_enter(void *func, void *caller) {
  push(&stack, clock());
  printf("ENTER :");
  print_func_name(func);
  printf(" to ");
  print_func_name(caller);
  printf("\n");
}

void no_attribute __cyg_profile_func_exit(void *func, void *caller) {
  clock_t end = clock();
  clock_t start = pop(&stack);
  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

  printf("EXIT :");
  print_func_name(func);
  printf(" to ");
  print_func_name(caller);
  printf(" in %f seconds\n", elapsed);
}

__attribute__((constructor)) static void init_profiler() { initStack(&stack); }
