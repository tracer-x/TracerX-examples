/*
 * Input a sequence of integers and store them in a binary search
 * tree.
 *
 * Copyright 2017 National University of Singapore
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

#ifdef DEBUG
#define N 9

int input[N] = {5, 6, 7, 8, 0, 1, 2, 3, 4, };
#else
#define N 5

int input[N]; // make SYMBOLIC in tracerx
#endif

struct node {
    int val;
    struct node *left, *right;
} *bst = NULL;

#define makenode(x, key) { \
    x = (struct node *) malloc(sizeof(struct node)); \
    x->val = key; \
    x->left = x->right = NULL; \
  }


void search_insert(struct node *, int);

#ifdef DEBUG
void print_tree(struct node *);
#endif

int main() {
    int i;

#ifdef LLBMC
  for (int j = 0; j < N; ++j) {
    input[j] = __llbmc_nondef_int();
  }
#else
    klee_make_symbolic(input, N * sizeof(int), "input");
#endif

    makenode(bst, input[0]);
    for (i = 1; i < N; i++)
      search_insert(bst, input[i]);

#ifdef DEBUG
    print_tree(bst);
#endif
    return 0;
}
    
void search_insert(struct node *bst, int key) {
   // printf("> %d\n", key);
   if (bst->val == key) return; 
   if (key < bst->val) {
     if (bst->left) search_insert(bst->left, key);
     else makenode(bst->left, key);
   } else {
     if (bst->right) search_insert(bst->right, key);
     else makenode(bst->right, key);
   }
}

#ifdef DEBUG
void print_tree(struct node *bst) {
  if (!bst) {
    printf("NULL");
    return;
  }
  printf("(");
  print_tree(bst->left);
  printf(" %d ", bst->val);
  print_tree(bst->right);
  printf(")");
}    
#endif
