/*
 * treecmp - Comparing KLEE path files in two separate directories.
 *
 * Copyright 2016, 2017 National University of Singapore
 *
 * WARNING: For this utility to compute statistics as intended,
 * Tracer-X KLEE must be run using -subsumed-test option. So that path
 * information is generated, even from subsumed paths.
 *
 * The first directory contains path files for KLEE runs without
 * abstraction learning. The second directory contains path files for
 * KLEE runs with abstraction learning (Tracer-X). This utility prints
 * consecutively three numbers in one line:
 *
 * 1) The number of proper extensions in the first directory, of a
 *    path in the second directory minus the number of those paths in
 *    the second directory that are being extended.
 * 2) The number of paths in the second directory, that are never
 *    traversed in the first directory.
 * 3) The number of paths in the first directory that is never visited
 *    by the tree of the second directory. (Specifically, this is a
 *    count of the tree leaves of the first directory that is never
 *    visited by the tree of the second directory.
 * 4) The earliest time the last path in the second directory is
 *    visited by the paths in the first directory. Time here is the
 *    number of the path files in the first directory, which can be
 *    read from the file name. -1 if the last path in the second
 *    directory is never visited by any path of the first directory.
 */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

struct tnode {
  int leaves_count;
  int min_time_reached; /* The earliest time this node is reached: It
			   is the number of the path file (from the
			   file name) */
  struct tnode *left;
  struct tnode *right;
  int visited;          /* Non-zero if visited by some prefix of a
		           path of the second directory */
};

struct tnode *global_root = NULL;

struct tnode *new_tnode(int time) {
  struct tnode *new_node = (struct tnode *)malloc(sizeof(struct tnode));
  new_node->leaves_count = 0;
  new_node->min_time_reached = time;
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->visited = 0;
  return new_node;
}

void remove_tree( struct tnode *root) {
  if (!root)
    return;
  remove_tree(root->left);
  remove_tree(root->right);
  free(root);
}

void print_usage(char *name) {
  fprintf(stderr, "Usage: %s dir1 dir2\n", name);
  fprintf(stderr, "dir1 - dir1/*.path are KLEE path files for run without abstraction learning\n");
  fprintf(stderr, "dir2 - dir2/*.path are KLEE path files for run with abstraction learning\n");  
}

void print_tree(int depth, struct tnode *n) {
  char str[BUFFER_SIZE];

  if (n == NULL) {
    printf("\n");
    return;
  }
  
  printf("%d: %d %d\t", depth, n->leaves_count, n->min_time_reached);
  printf("left: "); 
  print_tree(depth + 1, n->left);
  printf("right: ");
  print_tree(depth + 1, n->right);
}

void count_leaves(struct tnode *n) {
  if (n->left == NULL && n->right == NULL) {
    n->leaves_count = 1;
    return;
  }

  if (n->left) {
    count_leaves(n->left);
    n->leaves_count += n->left->leaves_count;
  }

  if (n->right) {
    count_leaves(n->right);
    n->leaves_count += n->right->leaves_count;
  }  
}

/* Linked list of leaves for counting of the number of leaves not
   covered. */
struct leaf {
  struct tnode *node;
  struct leaf *next;
};

struct leaf *leaf_list_head = NULL;

void add_leaf(struct tnode *node) {
  struct leaf *new_leaf = (struct leaf *)malloc(sizeof(struct leaf));
  new_leaf->node = node;
  new_leaf->next = leaf_list_head;
  leaf_list_head = new_leaf;
}

void clear_leaves() {
  struct leaf *p = leaf_list_head;

  while (p) {
    struct leaf *current = p;
    p = p->next;
    free(p);
  }
}

int uncovered_leaves() {
  struct leaf *current = leaf_list_head;
  int res = 0;
  
  while (current != NULL) {
    struct tnode *n = current->node;
    if (n->visited == 0) {
      res++;
    }
    current = current->next;
  }
  
  return res;
}

int main(int argc, char **argv) {
  DIR *dir1_f, *dir2_f;
  struct dirent *dir1, *dir2;
  struct tnode *current;
  
  if (argc < 3) {
    print_usage(argv[0]);
    return 1;
  }

  if ((dir1_f = opendir(argv[1])) == NULL) {
    print_usage(argv[0]);
    return 1;
  }

  if ((dir2_f = opendir(argv[2])) == NULL) {
    print_usage(argv[0]);
    closedir(dir1_f);
    return 1;
  }

  global_root = new_tnode(1);

  while ((dir1 = readdir(dir1_f)) != NULL) {
    int l = strlen(dir1->d_name);
    if (l < 6)
      continue;

    current = global_root;
    
    char *p = dir1->d_name + l - 5;
    if (!strcmp(p, ".path")) {
      FILE *fp;
      char file_name[BUFFER_SIZE], line_buf[BUFFER_SIZE];
      int time;

      /* Get the "time" of the path */
      sscanf(dir1->d_name, "test%6d.path", &time);

      sprintf(file_name, "%s/%s", argv[1], dir1->d_name);
      
      if ((fp = fopen(file_name, "r")) == NULL) {
	continue;
      }

      while (fgets(line_buf, BUFFER_SIZE, fp) != NULL) {
	switch (*line_buf) {
	case '0': {
	  if (!current->left) {
	    current->left = new_tnode(time);
	  }
	  if (current->min_time_reached > time) {
	    current->min_time_reached = time;
	  }
	  current = current->left;
	  break;
	}
	case '1': {
	  if (!current->right) {
	    current->right = new_tnode(time);
	  }
	  if (current->min_time_reached > time) {
	    current->min_time_reached = time;
	  }
	  current = current->right;
	  break;
	}
	default:
	  break;
	}
      }

      /* Add the last node to leaves linked list */
      add_leaf(current);
      fclose(fp);

    } else {
      /* Not a .path file */
      continue;
    }
  }

  closedir(dir1_f);

  // print_tree(0, global_root);

  count_leaves(global_root);

  // print_tree(0, global_root);
  
  int uncovered_path_count = 0;
  int saved_traversal = 0;

  /* Of the latest-generated second directory paths scanned in so far,
     if it is reached by a path in the first directory, this is the
     fastest time it is reached. Otherwise, this is -1. */
  int fastest_time_reached = -1;

  while ((dir2 = readdir(dir2_f)) != NULL) {
    int l = strlen(dir2->d_name);
    int max_time = -1;
    
    if (l < 6)
      continue;

    char *p = dir2->d_name + l - 5;
    if (!strcmp(p, ".path")) {
      FILE *fp;
      char file_name[BUFFER_SIZE], line_buf[BUFFER_SIZE];
      int uncovered_path = 0;
      int time;
      
      /* Time the path of the first directory reached earliest. */
      int time_reached; 

      /* Get the "time" of the path, this time we want to determine if
	 this was the latest-generated path. */
      sscanf(dir2->d_name, "test%6d.path", &time);
      
      if (time > max_time) {
	/* This is the latest-generated path scanned in so far */
	max_time = time;
      }
      
      sprintf(file_name, "%s/%s", argv[2], dir2->d_name);

      if ((fp = fopen(file_name, "r")) == NULL) {
	continue;
      }

      current = global_root;
      current->visited = 1;
      
      while (fgets(line_buf, BUFFER_SIZE, fp) != NULL) {
	switch (*line_buf) {
	case '0': {
	  if (!current->left) {
	    uncovered_path = 1;
	    uncovered_path_count++;
	    break;
	  }
	  current = current->left;
	  current->visited = 1;
	  break;
	}
	case '1': {
	  if (!current->right) {
	    uncovered_path = 1;
	    uncovered_path_count++;
	    break;
	  }
	  current = current->right;
	  current->visited = 1;
	  break;
	}
	default:
	  break;
	} 
	time_reached = current->min_time_reached;
	if (uncovered_path) {
	  break;
	}
      }

      if (!uncovered_path &&
	  (current->left != NULL || current->right != NULL)) {
	/* We reduce one path as the subsumed path itself is not
	   saved. */
	saved_traversal += (current->leaves_count - 1);
      }

      if (time == max_time) {
	if (!uncovered_path) {
	  fastest_time_reached = time_reached;
	} else {
	  fastest_time_reached = -1;
	}
      }
      
      fclose(fp);

    } else {
      /* Not a .path file */
      continue;
    }
    
  }
  
  closedir(dir2_f);

  int ul = uncovered_leaves();

  /* Deallocate used memory */
  clear_leaves();
  remove_tree(global_root);

  /* Print results */
  printf("%d %d %d %d\n", saved_traversal, uncovered_path_count, (ul - saved_traversal), fastest_time_reached);
  
  return 0;
}

