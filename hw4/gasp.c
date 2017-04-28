/*
 * Graham Kelly, CSE 374 Assignment 4, 4/27/17
 * a simple C program that processes files and 
 * prints info about them to stdout.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PAT 100
#define MAX_LN 500

// global declarations (defns later)
int ignore;
int number;

// function declarations (defns and descs below)
int  _get_tmp_str(char *line, char tmp[]);
int _process_file(char *fname, char *pattern);

// reads command line args to set options,
// and read lines from file and print lines w/
// matches.
int main(int argc, char *argv[]) {
  ignore = 0;  // initializing global (ignore case) to 0 (no)
  number = 0;  // initializing global (print line no.) to 0 (no)
  char *pattern = NULL;  // to hold the user's pattern
  int option_args = 0;  // tracks the number of option CL args

  for (int i = 1; i < argc; i++) {  // look at each arg
    if (ignore == 0 && strncmp(argv[i], "-i", 2) == 0) {
      ignore = 1;  // set ignore case to yes
      option_args++;
    } else if (number == 0 && strncmp(argv[i], "-n", 2) == 0) {
      number = 1;  // set print line no. to yes
      option_args++;
    } else {
      if (pattern == NULL) {  // we haven't gotten a pattern yet.
        pattern = argv[i];  // keep pointer to CL arg.
        if (ignore == 1) {
          // change pattern to lowercase
          for (char *p = pattern; *p; ++p) *p = tolower(*p);
        }
      } else {  // all other args are files to be processed.
        _process_file(argv[i], pattern);
      }
    }
  }
  // print err msg if not enough args supplied.
  // ok to execute down here since certain statements
  // in loop won't execute if args aren't properly supplied.
  if ((argc - option_args) < 3) {
    fprintf(stderr, "Too few args supplied.\n");
  }
  return 0;
}

// checks each line of file matching passed fname.
// if the line contains the passed pattern (ignoring
// case if this option is set) then the line is printed
// to the console (with the corresponding line number
// from the file if that option is set).
int _process_file(char *fname, char *pattern) {
  FILE* file = fopen(fname, "r");  // pointer to file
  char line[MAX_LN];  // to store each line of the file
  int i = 1;

  if ( !(file) ) {  // if file cannot be opened (might not exist)
    fprintf(stderr, "Unable to open file: %s\n", fname);
  } else {
    while ( fgets(line, MAX_LN, file) ) {  // essentially foreach line
      char tmp[MAX_LN];  // init storage for tmp (would be easier w malloc)
      _get_tmp_str(line, tmp);  // fill tmp
      if (strstr(tmp, pattern) != NULL) {
        if (number == 1) {
          printf("%d %s", i, line);  // print line no as well if specified.
        } else {
          printf("%s", line);
        }
      }
      i++;
    }
    fclose(file);
    if ( ferror(file) ) {  // check if we had an error during fgets calls.
      fprintf(stderr, "There was an error reading file: %s at line %d.\n",
              fname, i);
    }
  }
  return 0;
}

// if ignore case is set, this function fills the passed tmp
// array with a lowercase version of the passed string line
// else, just copies line into tmp with no changes.
int _get_tmp_str(char *line, char tmp[]) {
  if (ignore == 1) {
    strncpy(tmp, line, strlen(line));
    // change line to lowercase (if ignore case set).
    for (char *p = tmp; *p; ++p) *p = tolower(*p);
  } else {
    strncpy(tmp, line, strlen(line));
  }
  return 0;
}
