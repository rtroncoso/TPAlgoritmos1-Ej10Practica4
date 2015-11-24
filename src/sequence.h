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

#ifndef _SEQUENCE_H
#define _SEQUENCE_H

#define MAX_CHARS 35565

#include <stdlib.h>
#include <stdio.h>

// Sequence Definition
typedef struct s_sequence 
{
  FILE *file_ptr;
} t_sequence;
typedef t_sequence *seq_ptr;

// Function Declarations
void seq_prepare(seq_ptr *seq, const char *file_path);
void seq_write(seq_ptr *seq, char c);
void seq_close(seq_ptr *seq);
char seq_read_first(seq_ptr *seq);
char seq_read_next(seq_ptr *seq);
int seq_end(seq_ptr *seq);

#endif