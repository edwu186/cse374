/* Graham Kelly 5/11/2017
 * University of Washington, CSE 374: Assignment 5
 *
 * This is the main module for an autocomplete program.
 * This loads the file identified by first CL arg into 
 * trie datastructure then reads from stdin. Input from
 * stdin is then passed back to trie and all words with
 * matching prefix are printed in post order.
 */

#include "trie.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// your basic main function :)
int main(int argc, char **argv) {
  if (argc < 1 || argv[1] == NULL) {  // improperly called
    fprintf(stderr, "Invalid arguments supplied.\n");
    exit(1);
  }

  Trie *trie = new_trie();  // init trie

  FILE *fp;
  if ((fp = fopen(argv[1], "r")) != NULL) {
    char word[ MAX_STR_LEN ];  // buffer to store each word
    while (!feof(fp)) {
      fscanf(fp, "%s", word);
      trie = add(trie, word);  // reassign to new trie (post add)
    }
    fclose(fp);
  } else {  // inform and exit if problem opening file.
    fprintf(stderr, "Unable to open file.\n");
    exit(1);
  }

  char prefix[ MAX_STR_LEN ];  // buffer to store prefix
  while (!feof(stdin)) {
    int c = scanf("%s", prefix);  // read input to buffer
    if (c > 0) {  // if prefix nonempty
      autocomplete(trie, prefix);
    }
  }
  deallocate_node(trie);  // return mem from trie.
  return 0;
}
