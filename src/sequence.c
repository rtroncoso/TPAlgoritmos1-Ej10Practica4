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

#include "sequence.h"
#include "log.h"

/**
 * Creates a sequence structure by using a file path and a file
 * 
 * @param seq Sequence pointer
 * @param file_path
 * @return void
 */
void seq_prepare(seq_ptr *seq, const char *file_path)
{
  *seq = (seq_ptr) malloc(sizeof(t_sequence));
  if(seq != NULL) {
    (*seq)->file_ptr = fopen(file_path, "rb+");
    if((*seq)->file_ptr == NULL) {
      (*seq)->file_ptr = fopen(file_path, "wb");
    }
  }
}

/**
 * Writes a character into a sequence
 * 
 * @param seq Sequence pointer
 * @param c Character to write
 * @return void
 */
void seq_write(seq_ptr *seq, char c)
{
  fputc(c, (*seq)->file_ptr);
}

/**
 * Closes the file stream (marcar)
 * 
 * @param seq Sequence pointer
 * @return void
 */
void seq_close(seq_ptr *seq)
{
  fclose((*seq)->file_ptr);
}

/**
 * Reads the first character from the stream
 * 
 * @param seq Sequence pointer
 * @return char Character read
 */
char seq_read_first(seq_ptr *seq)
{
  return seq_read_next(seq);
}

/**
 * Reads the next character from the stream
 * 
 * @param seq Sequence pointer
 * @return char Character read
 */
char seq_read_next(seq_ptr *seq)
{
  return fgetc((*seq)->file_ptr);
}

/**
 * Returns if the file being read ended or not
 * 
 * @param seq Sequence pointer
 * @return int 1 for eof
 */
int seq_end(seq_ptr *seq)
{
  return feof((*seq)->file_ptr);
}
