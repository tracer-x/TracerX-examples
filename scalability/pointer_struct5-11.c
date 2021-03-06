/*
 * Input a sequence of integers and store them in a list
 * representation of a bag (multiset)
 *
 * Copyright 2017 National University of Singapore
 */

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif
#include <stdlib.h>

#define N 11

int input[N];

struct node {
    int val, freq;
    struct node *next;
} *mybag = NULL, *list, *tail;

int main(int argc, char **argv) {
  int i;

#ifdef LLBMC
  for (int j = 0; j < N; ++j) {
    input[j] = __llbmc_nondef_int();
  }
#else
  klee_make_symbolic(input, N * sizeof(input[0]), "input");
#endif

  for (i = 0; i < N; i++) {
    list = mybag;
    while (list) {
      if (input[i] == list->val) { // ***
	list->freq++;
	break;
      }
      else {
	tail = list;
	list = list->next;
      }
    }
    if (!list)  {
      if (!tail) mybag = tail = malloc(sizeof(struct node));
    } else {
      tail->next = malloc(sizeof(struct node));
      tail = tail->next;
    }
    tail->val = input[i];
    tail->next = NULL;
  }

  return 0;
}

