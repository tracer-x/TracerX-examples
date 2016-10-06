/* 
 * Comparing KLEE path files in two separate directories. The first
 * directory contains path files for KLEE runs without lazy
 * annotation. The second directory contains path files for KLEE runs
 * with lazy annotation. This utility prints two numbers in separate
 * lines: The first number is the number of proper extensions in the
 * first directory, of a path in the second directory. The second
 * number is the number of paths in the second directory, that are
 * never traversed in the first directory.
 */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

struct tnode {
  int leaves_count;
  struct tnode *left;
  struct tnode *right;
};

struct tnode *global_root = NULL;

struct tnode *new_tnode() {
  struct tnode *new_node = (struct tnode *)malloc(sizeof(struct tnode));
  new_node->leaves_count = 0;
  new_node->left = NULL;
  new_node->right = NULL;
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
  fprintf(stderr, "dir1 - dir1/*.path are KLEE path files for run without lazy annotation\n");
  fprintf(stderr, "dir2 - dir2/*.path are KLEE path files for run with lazy annotation\n");  
}

void print_tree(int depth, struct tnode *n) {
  char str[BUFFER_SIZE];

  if (n == NULL) {
    printf("\n");
    return;
  }
  
  printf("%d: %d\t", depth, n->leaves_count);
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

  global_root = new_tnode();

  while (dir1 = readdir(dir1_f)) {
    int l = strlen(dir1->d_name);
    if (l < 6)
      continue;

    current = global_root;
    
    char *p = dir1->d_name + l - 5;
    if (!strcmp(p, ".path")) {
      FILE *fp;
      char file_name[BUFFER_SIZE], line_buf[BUFFER_SIZE];

      sprintf(file_name, "%s/%s", argv[1], dir1->d_name);
      
      if ((fp = fopen(file_name, "r")) == NULL) {
	continue;
      }

      while (fgets(line_buf, BUFFER_SIZE, fp) != NULL) {
	switch (*line_buf) {
	case '0': {
	  if (!current->left) {
	    current->left = new_tnode();
	  }
	  current = current->left;
	  break;
	}
	case '1': {
	  if (!current->right) {
	    current->right = new_tnode();
	  }
	  current = current->right;
	  break;
	}
	default:
	  break;
	}
      }
      
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

  while (dir2 = readdir(dir2_f)) {
    int l = strlen(dir2->d_name);
    if (l < 6)
      continue;

    char *p = dir2->d_name + l - 5;
    if (!strcmp(p, ".path")) {
      FILE *fp;
      char file_name[BUFFER_SIZE], line_buf[BUFFER_SIZE];
      int uncovered_path = 0;

      sprintf(file_name, "%s/%s", argv[2], dir2->d_name);

      if ((fp = fopen(file_name, "r")) == NULL) {
	continue;
      }

      current = global_root;

      while (fgets(line_buf, BUFFER_SIZE, fp) != NULL) {
	switch (*line_buf) {
	case '0': {
	  if (!current->left) {
	    uncovered_path = 1;
	    uncovered_path_count++;
	    break;
	  }
	  current = current->left;
	  break;
	}
	case '1': {
	  if (!current->right) {
	    uncovered_path = 1;
	    uncovered_path_count++;
	  }
	  current = current->right;
	  break;
	}
	default:
	  break;
	} 
	if (uncovered_path) {
	  break;
	}
      }

      if (!uncovered_path &&
	  (current->left != NULL || current->right != NULL)) {
	saved_traversal += current->leaves_count;
      }
      
      fclose(fp);

    } else {
      /* Not a .path file */
      continue;
    }
    
  }
  
  closedir(dir2_f);

  printf("%d\n", saved_traversal);
  printf("%d\n", uncovered_path_count);
  
  return 0;
}

