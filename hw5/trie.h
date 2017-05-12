/* Graham Kelly 5/11/2017
 * University of Washington, CSE 374: Assignment 5
 *
 * This is a header file for an autocomplete program.
 * Here we declare the struct and functions necessary
 * for our trie implementation that will be used by
 * main module to autocomplete.
 */
#ifndef TRIE_H
#define TRIE_H
#define MAX_STR_LEN 500

// node in trie to store data and children
typedef struct trie_node Trie;

// returns pointer to empty trie.
Trie* new_trie();

// returns pointer to trie constructed from passed trie (can be null)
// with the passed string added to it (this could be a duplicate string,
// or an empty string; nothing would happen)
Trie* add(Trie *trie, char *str);

// prints to stdout the valid words that are children of the passed trie
void print_trie(Trie *trie, char *path);

// prints all valid words starting with passed prefix
// that occur in passed trie (either can be null)
void autocomplete(Trie *trie, char *prefix);

// deallocates all mem used by passed trie
void deallocate_node(Trie *trie);
#endif  // TRIE_H
