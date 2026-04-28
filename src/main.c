#include <stdio.h>
#include <unistd.h>

#define no_attribute __attribute__((no_instrument_function))

void busy_delay(long loops) {
  for (volatile long i = 0; i < loops; i++)
    ;
}

int factorial(int n) {
  if (n <= 1)
    return 1;
  return n * factorial(n - 1);
}

int fibonacci(int n) {
  if (n <= 1)
    return n;
  return fibonacci(n - 1) + fibonacci(n - 2);
}

void level3() { busy_delay(200000000); }

void level2() {
  level3();
  busy_delay(100000000);
}

void level1() {
  level2();
  level3();
}

void workload() {
  factorial(10);
  fibonacci(10);
  level1();
}

int no_attribute main(void) {
  printf("Starting profiler demo...\n");

  workload();

  printf("Running additional calls...\n");

  level1();
  factorial(5);

  printf("Done.\n");
  return 0;
}
