/* -*- mode: c; c-file-style: "openbsd" -*- */
/*
 * Copyright (c) 2015 Rodrigo Troncoso <rod.tronco@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "main.h"
#include "log.h"
#include "stack.h"
#include "sequence.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>

#define TMP_SEQUENCE "sequence.in"

extern const char *__progname;

/**
 * Shows usage options for the program
 *
 * @return void
 */
static void usage(void)
{
  fprintf(stderr, "Usage: %s [OPTIONS]\n",
      __progname);
  fprintf(stderr, "Version: %s\n", PACKAGE_STRING);
  fprintf(stderr, "\n");
  fprintf(stderr, " -d, --debug        be more verbose.\n");
  fprintf(stderr, " -t, --test         performs tests on implementations\n");
  fprintf(stderr, " -h, --help         display help and exit\n");
  fprintf(stderr, " -v, --version      print version and exit\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "see manual page " PACKAGE "(8) for more information\n");
}

/**
 * Output a nice and tidy welcome message and
 * description!
 *
 * @return void
 */
static void description()
{
  printf("=============== ABSTRACT TYPES C IMPLEMENTATION ===============\n");
  printf("This program will accomplish the required assignments for the 10th exercise\n");
  printf("in the students book given by <Patricia Mayor(pmayor@caece.edu.ar)>.\n");
  printf("The assignments are as follows:\n");
  printf("\n");
  printf("The program should receive an input sequence of characters and store all\n");
  printf("non-numerical characters in a stack. When a numerical character is found,\n");
  printf("the program must remove from the stack as many characters as this number\n");
  printf("indicates, or all the available characters on the stack if this number\n");
  printf("exceeds the amount of characters in the input sequence.\n");
  printf("\n");
  printf("For further instructions run this command with the -(-h)elp option\n");
  printf("or see the manual page for this program using man %s\n", __progname);
  printf("===============================================================\n\n");
}

/**
 * Performs simple tests for abstract types implementations
 *
 * @return void
 */
static void test(void)
{
  char a = 'b';
  stack_ptr stack = NULL;
  seq_ptr seq = NULL;

  seq_prepare(&seq, "sequence.test");
  seq_write(&seq, 'o');
  seq_init(&seq);
  log_info("main", "Character written in sequence: %c", a = seq_read_first(&seq));
  seq_close(&seq);

  stack_create(&stack);
  log_info("main", "Stack is: %s", stack_empty(&stack) ? "Empty" : "Not empty");
  stack_push(&stack, a);
  log_info("main", "Stack is: %s", stack_empty(&stack) ? "Empty" : "Not empty");
  log_info("main", "First character in stack: %c", stack_pop(&stack));
  log_info("main", "Stack is: %s", stack_empty(&stack) ? "Empty" : "Not empty");
}

/**
 * Solves the exrecise
 *
 * Exercise 10 from the 4th workbook
 * 
 * @param seq Sequence pointer
 * @param stack Stack pointer
 * @return void
 */
static void solve_exercise(seq_ptr *seq, stack_ptr *stack)
{
  char c; int aux = 0;
  if( ! seq_end(seq)) c = seq_read_first(seq);

  while( ! seq_end(seq) && ! stack_full(stack)) {
    if( ! isdigit(c)) {
      stack_push(stack, c);
    } else {
      aux = atoi(&c);
      while(aux > 0 && ! stack_empty(stack)) {
        stack_pop(stack);
        aux--;
      }
    }
    c = seq_read_next(seq);
  }

  seq_close(seq);
}

/**
 * In case there is no file passed to the command line input,
 * the user will be prompted for a sequence of characters inserted
 * via keyboard.
 * 
 * @param seq Sequence pointer
 * @return void
 */
static void prompt_user(seq_ptr *seq)
{
  char c;
  printf("It seems as there is no input file being prompted into the program.\n");
  do {
    printf("Do you want to enter a sequence through this command line?: (y/n)\n");
    scanf("%c", &c);
  } while(c != 'y'  && c != 'n');

  if(c == 'y') {
    printf("Insert the sequence of characters (press enter to finish):\n");
    char *str = (char *) malloc(sizeof(str) * 1024);
    scanf (" %[^\n]s", str);

    for(unsigned long i = 0; i < strlen(str); i++) {
      seq_write(seq, str[i]);
    }
  } else {
    exit(0);
  }
}

int main(int argc, char *argv[])
{
  int debug = 1;
  int ch;
  char *file_path = NULL;

  static struct option long_options[] = {
                { "test", no_argument, 0, 't' },
                { "input", no_argument, 0, 'i' },
                { "debug", no_argument, 0, 'd' },
                { "help",  no_argument, 0, 'h' },
                { "version", no_argument, 0, 'v' },
    { 0 },
    { 0 }
  };
  while (1) {
    int option_index = 0;
    ch = getopt_long(argc, argv, "hvdtD:i:",
        long_options, &option_index);
    if (ch == -1) break;
    switch (ch) {
    case 'h':
      usage();
      exit(0);
      break;
    case 'v':
      fprintf(stdout, "%s\n", PACKAGE_VERSION);
      exit(0);
      break;
    case 'd':
      debug++;
      break;
    case 'D':
      log_accept(optarg);
      break;
    case 'i':
      file_path = optarg;
      break;
    case 't':
      log_init(2, __progname);
      test();
      exit(0);
      break;
    default:
      fprintf(stderr, "unknown option `%c'\n", ch);
      usage();
      exit(1);
    }
  }

  // Setup program
  log_init(debug, __progname);
  log_info("main", "hello world!");
  description();

  // Create abstract types variables
  seq_ptr seq = NULL;
  stack_ptr stack = NULL;

  // Initialize and solve exercise
  if(file_path == NULL) {
    seq_prepare(&seq, TMP_SEQUENCE);
    prompt_user(&seq);
    seq_init(&seq);
  } else {
    seq_prepare(&seq, file_path);
  }
  stack_create(&stack);
  solve_exercise(&seq, &stack);
  printf("[OUTPUT] The result for the algorithm is the following:\n");
  stack_output(&stack);

  // Clean up and return success
  if(file_path == NULL) remove(TMP_SEQUENCE);
  return EXIT_SUCCESS;
}

