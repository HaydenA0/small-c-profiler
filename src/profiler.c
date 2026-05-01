#define _GNU_SOURCE
#include "profiler.h"
#include "timestack.h"
#include <dlfcn.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

// BUG : json writing has a small bug where it adds a comma after the last

#define no_attribute __attribute__((no_instrument_function))

static TimeStack stack;
static FILE *trace_file;

void no_attribute print_func_name(void *func) {
  Dl_info info;
  if (dladdr(func, &info) && info.dli_sname) {
    printf("%s", info.dli_sname);
  } else {
    printf("Unknown name, address : %p", func);
  }
}

const char *no_attribute get_func_name(void *func) {
  Dl_info info;
  if (dladdr(func, &info) && info.dli_sname) {
    return info.dli_sname;
  }
  return "unknown";
}

void no_attribute __cyg_profile_func_enter(void *func, void *caller) {
  clock_t start_time = clock();
  push(&stack, start_time);
  if (trace_file) {
    fprintf(trace_file,
            "\n{\"name\": \"%s\", \"ph\": \"B\", \"ts\": %llu, \"pid\": 1, "
            "\"tid\": 1},",
            get_func_name(func), (unsigned long long)start_time);
  }
}

void no_attribute __cyg_profile_func_exit(void *func, void *caller) {
  clock_t end_time = clock();
  clock_t start_time = pop(&stack);
  double elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  if (trace_file) {
    fprintf(trace_file,
            "\n{\"name\": \"%s\", \"ph\": \"E\", \"ts\": %llu, \"pid\": 1, "
            "\"tid\": 1},",
            get_func_name(func), (unsigned long long)end_time);
  }
}

__attribute__((constructor)) static void init_profiler() {
  initStack(&stack);
  trace_file = fopen("trace.json", "w");
  fprintf(trace_file, "[\n");
}

__attribute__((destructor)) static void close_profiler() {
  if (trace_file) {
    fprintf(trace_file, "\n]");
    fclose(trace_file);
    trace_file = NULL;
  }
}
