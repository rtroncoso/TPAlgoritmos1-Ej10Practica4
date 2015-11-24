/* -*- mode: c; c-file-style: "openbsd" -*- */
/*
 * Copyright (c) 2014 Rodrigo Troncoso <rod.tronco@gmail.com>
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

#ifndef _STACK_H
#define _STACK_H

#include <stdlib.h>
#include <stdio.h>
 
typedef char t_data;

// Stack Node Definition
typedef struct s_node 
{
  t_data data;
  struct s_node *next;
} t_node;

// Type Definitions
typedef t_node *node_ptr;
typedef t_node *stack_ptr;

// Function Interfaces
void stack_create(stack_ptr *stack);
void stack_push(stack_ptr *stack, t_data x);
t_data stack_pop(stack_ptr *stack);
int stack_empty(stack_ptr *stack);
int stack_full(stack_ptr *stack);

#endif