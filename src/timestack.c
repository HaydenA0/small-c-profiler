#include "timestack.h"
#include <stdio.h>

void no_attribute initStack(TimeStack *stack) { stack->top = 0; }

bool no_attribute isEmpty(TimeStack *stack) { return stack->top == 0; }

bool no_attribute isFull(TimeStack *stack) { return stack->top == MAX_SIZE; }

void no_attribute push(TimeStack *stack, clock_t val) {
  if (isFull(stack)) {
    printf("Clock Stack is full\n");
    return;
  }
  stack->arr[stack->top++] = val;
}

clock_t no_attribute pop(TimeStack *stack) {
  if (isEmpty(stack)) {
    printf("Clock Stack is empty\n");
    return clock();
  }
  return stack->arr[--stack->top];
}

clock_t no_attribute peek(TimeStack *stack) {
  if (isEmpty(stack)) {
    printf("Clock Stack is empty\n");
    return clock();
  }
  return stack->arr[stack->top - 1];
}
