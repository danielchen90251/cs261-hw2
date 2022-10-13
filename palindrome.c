#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"
#include "queue.h" 

#define MAX_STR_LEN 256

/*
 * This function prompts the user for input and stores a maximum of `n`
 * characters of the string they enter into `dest`.  Any trailing line ending
 * characters are removed from the input string.  Returns 1 if a string was
 * successfully read from the user or 0 otherwise.
 */
int get_user_str(char* dest, int n) {
  printf("\nEnter a string, and we'll check whether it's a palindrome:\n");
  if (fgets(dest, MAX_STR_LEN, stdin) != NULL) {
    /*
     * If a string was successfully read from the user, remove any trailing
     * line ending characters.  Here's some documentation on strcspn() to help
     * understand how this works:
     *
     * https://en.cppreference.com/w/c/string/byte/strcspn
     */
    dest[strcspn(dest, "\r\n")] = '\0';
    return 1;
  } else {
    return 0;
  }
}

int main(int argc, char const *argv[]) {
  char* in = malloc(MAX_STR_LEN * sizeof(char));

  struct queue* q;
  struct stack* s;

  while (get_user_str(in, MAX_STR_LEN)) {
    /*
     * Inside this loop body, you'll have an input string from the user in `in`.
     * You should use your stack and your queue to test whether that string is
     * a palindrome (i.e. a string that reads the same backward as forward, e.g.
     * "ABCBA" or "Madam, I'm Adam").  For each string input by the user,
     * print a message letting the user know whether or not their string is
     * is a palindrome.
     *
     * When you test whether the user's string is a palindrome, you should
     * ignore any non-letter characters (e.g. spaces, numbers, punctuation,
     * etc.), and you should ignore the case of letters (e.g. the characters
     * 'a' and 'A' should be considered as equal).  The C functions isalpha()
     * and tolower() from ctype.h might help with this.
     */
    q = queue_create();
    s = stack_create();

    int i = 0;
    int size = 0;
    int flag = 1;

    while (in[i] != '\0'){
      // remove non-alphabet
      if (isalpha(in[i])) {
        //printf("%c", in[i]);
        queue_enqueue(q, &in[i]);
        stack_push(s, &in[i]);
        size += 1;
      }
      i += 1;
    }

    while (size --){
      char* dequeued = queue_dequeue(q);
      char* popped = stack_pop(s);
      if (tolower(*dequeued) != tolower(*popped)) {
        printf("OOPS! Not a palindrome!\n");
        flag = 0;
        break;
      }
    }
    if (flag){
      printf("Yes! it is a palindrome!\n");
    }
  }

  free(in);
  return 0;
}
