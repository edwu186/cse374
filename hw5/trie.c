/* Graham Kelly 5/11/2017
 * University of Washington, CSE 374: Assignment 5
 *
 * This file defines all trie functions and the struct
 * used to represent the trie. These definitions are used
 * by main module to facilitate autocomplete.
 */
#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHILD_NUM 128  // ascii char count.

// node in trie to store data and children
struct trie_node {
  int is_word;  // nonzero if this is end of valid word
  struct trie_node *children[ CHILD_NUM ];  // all children of node
};

// returns pointer to empty trie.
Trie* new_trie() {
  return NULL;
}

// returns pointer to trie constructed from passed trie (can be null)
// with the passed string added to it (this could be a duplicate string,
// or an empty string; nothing would happen)
Trie* add(Trie *trie, char *str) {
  if (trie == NULL) {
    trie = (Trie*) malloc(sizeof(Trie));
    if (trie == NULL) {  // check malloc result.
      fprintf(stderr, "Unable to allocate memory.\n");
      exit(1);
    }
  }

  Trie *root = trie;  // get pointer to root of trie
  int length = strlen(str);

  if (!(length >= 0)) {  // check if strlen worked.
    fprintf(stderr, "Failed to get length of string.\n");
    exit(1);
  }

  for (int i = 0; i < length; i++) {  // for every char of string...
    Trie *cur_trie = trie->children[(int)str[i]];  // get children of cur node

    if (cur_trie == NULL) {  // if this path hasn't been created yet...
      if ((cur_trie = (Trie*) malloc(sizeof(Trie))) != NULL) {
        // here if path didn't exist yet and malloc check passed above.
        cur_trie->is_word = 0;  // init new node
        for (int j = 0; j < CHILD_NUM ; j++) {  // init new node
          cur_trie->children[j] = NULL;
        }
      } else {  // inform and exit if malloc failed.
        fprintf(stderr, "Unable to allocate memory.\n");
        exit(1);
      }
    }

    if (length == i + 1) {  // check if we are at the end of a valid word
      cur_trie->is_word = 1;  // store this info in node if so.
    }

    trie->children[(int)str[i]] = cur_trie;  // make sure parent has right child
    trie = trie->children[(int)str[i]];  // 'recurse' down to child
  }

  return root;  // return pointer to root
}

// prints to stdout the valid words that are children of the passed trie
void print_tree(Trie *trie, char *path) {
  if (trie == NULL) {  // return if trie null
    return;
  }

  for (int i = 0; i < CHILD_NUM ; i++) {
    if (trie->children[i] != NULL) {
      int length = strlen(path);

      if (!(length >= 0)) {  // check if strnlen worked.
        fprintf(stderr, "Failed to get length of string.\n");
        exit(1);
      }
      char *new_path;  // to store new path
      char *next_step;  // to store next char in path

      if ((new_path = malloc(length + 2)) != NULL &&
          (next_step = malloc(2)) != NULL) {
        new_path[0] = '\0';  // init to empty for strcat
        next_step[0] = (char) i;  // this is str containing only next char
        next_step[1] = '\0';  // ensure we have end of str

        snprintf(new_path, MAX_STR_LEN, path);  // cat old path to new path
        snprintf(&new_path[length], MAX_STR_LEN, next_step);

        print_tree(trie->children[i], new_path);  // recurse on new path
        free(new_path);
        free(next_step);
      } else {  // malloc failed above for one of the strs
        fprintf(stderr, "Unable to allocate memory.\n");
        exit(1);
      }
    }
  }

  // print our current path if it's a valid word.
  if (trie->is_word) {
    printf("%s\n", path);
  }
}

// prints all valid words starting with passed prefix
// that occur in passed trie (either can be null)
void autocomplete(Trie *trie, char *prefix) {
  if (trie == NULL || prefix == NULL) {
    return;  // if either passed param is null do nothing.
  }
  int len = strlen(prefix);
  if (len >= 0) {
    for (int i = 0; i < len; i++) {  // advance trie to end of prefix
      if (trie->children[(int) prefix[i]] != NULL) {
        trie = trie->children[(int) prefix[i]];
      } else {  // here if prefix + char is not a word
        return;  // return and do nothing in this case.
      }
    }
    print_tree(trie, prefix);  // print all children from this point
  } else {
    fprintf(stderr, "Failed to get length of string.\n");
    exit(1);
  }
}

// deallocates all mem used by passed trie
void deallocate_node(Trie *trie) {
  if (trie != NULL) {
    for (int i = 0; i < CHILD_NUM; i++) {
      deallocate_node(trie->children[i]);  // recurse to children
    }
    free(trie);
  }
}
