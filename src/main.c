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

extern const char *__progname;

static void
usage(void)
{
  fprintf(stderr, "Usage: %s [OPTIONS]\n",
      __progname);
  fprintf(stderr, "Version: %s\n", PACKAGE_STRING);
  fprintf(stderr, "\n");
  fprintf(stderr, " -d, --debug        be more verbose.\n");
  fprintf(stderr, " -h, --help         display help and exit\n");
  fprintf(stderr, " -v, --version      print version and exit\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "see manual page " PACKAGE "(8) for more information\n");
}

int
main(int argc, char *argv[])
{
  int debug = 1;
  int ch;

  static struct option long_options[] = {
                { "debug", no_argument, 0, 'd' },
                { "help",  no_argument, 0, 'h' },
                { "version", no_argument, 0, 'v' },
    { 0 }
  };
  while (1) {
    int option_index = 0;
    ch = getopt_long(argc, argv, "hvdD:",
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
    default:
      fprintf(stderr, "unknown option `%c'\n", ch);
      usage();
      exit(1);
    }
  }

  log_init(debug, __progname);
  log_info("main", "hello world!");

  char a = 'b';
  stack_ptr stack = NULL;
  seq_ptr seq = NULL;

  seq_prepare(&seq, "sequence");
  seq_write(&seq, 'o');
  seq_close(&seq);

  seq_prepare(&seq, "sequence");
  log_info("main", "Character written in sequence: %c", a = seq_read_first(&seq));
  seq_close(&seq);

  stack_create(&stack);
  log_info("main", "Stack is: %s", stack_empty(&stack) ? "Empty" : "Not empty");
  stack_push(&stack, a);
  log_info("main", "Stack is: %s", stack_empty(&stack) ? "Empty" : "Not empty");
  a = (char) stack_pop(&stack);
  log_info("main", "First character in stack: %c", a);
  log_info("main", "Stack is: %s", stack_empty(&stack) ? "Empty" : "Not empty");

  return EXIT_SUCCESS;
}
