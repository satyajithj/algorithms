/**
 *	author: satyajith
 * 	program: basic stack implementation
 */

#include <stdbool.h>
#include <stdio.h>

#define STACK_SIZE 100

// stack structure definition
typedef struct {
	int arr[STACK_SIZE];
	int top;
} stack;

// method declaration
void init_stack(stack*);		// initialize stack elements to 0 and top to -1
bool is_stack_empty(stack*);	// check if stack is empty
void push(stack*, int);			// push an element on to stack
int pop(stack*);				// pop and element from stack

int main(int argc, char const* argv[]) {
	// stack sample program here
	return 0;
}

// initialize stack
void init_stack(stack* S) {
	for (int i = 0; i < STACK_SIZE; ++i)
		S->arr[i] = 0;
	S->top = -1;
}

// check if stack is empty
bool is_stack_empty(stack* S) { return ((S->top == -1) ? true : false); }

// push an element on top of stack
void push(stack* S, int x) {
	if (S->top == STACK_SIZE - 1) {
		printf("%s\n", "stack overflow");
		return;
	} else {
		S->arr[++(S->top)] = x;
	}
}

// pop an element from the stack
int pop(stack* S) {
	if (S->top == -1) {
		printf("%s\n", "stack underflow");
		return -1;
	} else {
		return S->arr[(S->top)--];
	}
}