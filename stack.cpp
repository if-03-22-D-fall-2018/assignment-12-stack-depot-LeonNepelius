#include "stack.h"
#include <stdio.h>

struct NodeImplementation
{
    Node next;
    void* data;
};

struct StackImplementation
{
    Node head;
    int count;
};


/**
 * Used to create a stack structure.
 * @return The newly created stack.
 */
Stack create_stack()
{
  Stack stack =(Stack) smalloc(sizeof(StackImplementation));
  stack->head = 0;
  stack->count = 0;
  return stack;
}

/**
 * Used to free all memory the supplied stack allocated.
 * @param stack The stack to be deleted.
 * @note delete structure, including the struct itself, but not the data!
 */
void delete_stack(Stack stack)
{
  Node current = stack->head;
  while (current != 0)
  {
    Node to_be_deleted = current;
    current = current->next;
    sfree(to_be_deleted);
  }
  sfree(stack);
}

/**
 * Adds a new node with the supplied data to the top of the stack.
 * @param stack The stack onto which data has to be pushed.
 * @param data The data to be pushed.
 */
void push_stack(Stack stack, void *data)
{
  Node to_be_pushed = (Node)smalloc(sizeof(NodeImplementation));
  to_be_pushed->next = stack->head;
  to_be_pushed->data = data;
  stack->head = to_be_pushed;
  stack->count++;
}

/**
 * @param stack The stack which number of elements to be retrieved.
 * @return The number of items currently on the stack.
 */
int get_count(Stack stack)
{
  return stack->count;
}

/**
 * Removes and returns the topmost item of the stack.
 * @param stack The stack from which to take.
 * @return The element returned from the stack.
 */
void* pop_stack(Stack stack)
{
  if (get_count(stack) == 0)
  {
      return 0;
  }
  Node to_be_deleted = stack->head;
  void* ret_data = to_be_deleted->data;
  stack->head = to_be_deleted->next;
  stack->count--;
  sfree(to_be_deleted);
  return ret_data;
}

/**
 * Returns the topmost item of the stack without removing it.
 * @param stack The stack from which to take.
 * @return The element returned from the stack.
*/
void* peek_stack(Stack stack)
{
  return stack->head->data;
}
