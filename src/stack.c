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

#include "stack.h"
#include "log.h"

/**
 * Creates a new node and assigns an empty value to it.
 *
 * @param stack Stores the newly created node pointer
 * @return void
 */
void stack_create(stack_ptr *stack)
{
  log_info("stack", "(stack_create): Creating a new empty node");
  *stack = (stack_ptr) malloc(sizeof(t_node));
  (*stack)->data = NULL;
  (*stack)->next = NULL;
}

/**
 * Pushes an element into the stack

 * @param stack Stack pointer
 * @param x     Element to be pushed into the stack
 * @return void
 */
void stack_push(stack_ptr *stack, t_data x)
{
  log_info("stack", "(stack_push): Adding a new node to stack with data: %c", x);
  node_ptr node;
  node = (node_ptr) malloc(sizeof(t_node));
  if(node != NULL) {
    node->data = x;
    node->next = *stack;
    *stack = node;
  }
}

/**
 * Pops an element from the stack
 
 * @param stack Stack pointer
 * @return void First element from the stack
 */
t_data stack_pop(stack_ptr *stack)
{
  node_ptr node;
  t_data x;

  node = *stack;
  x = (*stack)->data;
  *stack = (*stack)->next;
  free(node);

  log_info("stack", "(stack_pop): Removing node from stack: %c", (t_data) x);
  return x;
}

/**
 * Returns 0 or 1 depending on the stack status (empty or non-empty)
 *
 * @param stack Stack pointer
 * @return int 1 for empty stack, 0 for non-empty stack
 */
int stack_empty(stack_ptr *stack)
{
  return ((*stack)->next == NULL && (*stack)->data == NULL);
}
