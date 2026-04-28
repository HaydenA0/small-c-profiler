#ifndef PROFILER_H
#define PROFILER_H

#include <time.h>

void print_func_name(void *func);

void __attribute__((no_instrument_function))
__cyg_profile_func_enter(void *func, void *caller);

void __attribute__((no_instrument_function))
__cyg_profile_func_exit(void *func, void *caller);

#endif
