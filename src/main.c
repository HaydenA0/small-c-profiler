

#include "stdbool.h"
#include "stdio.h"
#include "time.h"
#define MAX_SIZE 100000
#define no_attribute __attribute__((no_instrument_function))

typedef struct {
  clock_t arr[MAX_SIZE];
  int top;
} StartStack;

void no_attribute initStack(StartStack *stack) { stack->top = 0; }
bool no_attribute isEmpty(StartStack *stack) { return stack->top == 0; }
bool no_attribute isFull(StartStack *stack) { return stack->top == MAX_SIZE; }

void no_attribute push(StartStack *stack, clock_t val) {
  if (isFull(stack)) {
    printf("Clock Stack is full\n");
    return;
  }
  stack->arr[stack->top++] = val;
}

clock_t no_attribute pop(StartStack *stack) {
  if (isEmpty(stack)) {
    printf("Clock Stack is empty\n");
    return clock();
  }
  return stack->arr[--stack->top];
}

clock_t no_attribute peek(StartStack *stack) {
  if (isEmpty(stack)) {
    printf("Clock Stack is empty\n");
    return clock();
  }
  return stack->arr[stack->top - 1];
}

StartStack stack;

void __attribute__((no_instrument_function))
__cyg_profile_func_enter(void *func, void *caller) {
  push(&stack, clock());

  printf("ENTER: %p from %p\n", func, caller);
}

void __attribute__((no_instrument_function))
__cyg_profile_func_exit(void *func, void *caller) {
  clock_t end = clock();
  clock_t start = pop(&stack);
  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("EXIT : %p to %p (%f)\n", func, caller, elapsed);
  printf("EXIT : %p to %p\n", func, caller);
}

int functiona(void) { return 0; }

int functionb(void) {
  for (volatile long i = 0; i < 1000000000; i++)
    ;
  return 0;
}

int functionc(void) { return 0; }

int no_attribute main(void) {

  initStack(&stack);
  functiona();
  functionb();
  functionc();

  return 0;
}
