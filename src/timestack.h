#ifndef TIMESTACK_H
#define TIMESTACK_H

#include <stdbool.h>
#include <time.h>

#define MAX_SIZE 100000
#define no_attribute __attribute__((no_instrument_function))

typedef struct {
  clock_t arr[MAX_SIZE];
  int top;
} TimeStack;

void no_attribute initStack(TimeStack *stack);
bool no_attribute isEmpty(TimeStack *stack);
bool no_attribute isFull(TimeStack *stack);
void no_attribute push(TimeStack *stack, clock_t val);
clock_t no_attribute pop(TimeStack *stack);
clock_t no_attribute peek(TimeStack *stack);

#endif
