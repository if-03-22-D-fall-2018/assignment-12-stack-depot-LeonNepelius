#include "depot.h"
#include "stack.h"

static void insert_new_stack(Depot depot, Product *product);

struct DepotImplementation
{
  Stack stack;
};


Depot create_depot()
{
  Depot depot = (Depot)smalloc(sizeof(DepotImplementation));
  depot->stack = create_stack();
  return depot;
}

void delete_depot(Depot depot)
{
  Stack stack;
  while(get_count(depot->stack) != 0){
    stack = (Stack)pop_stack(depot->stack);
		delete_stack(stack);
	}
	sfree(depot->stack);
	sfree(depot);
}

static void insert_new_stack(Depot depot, Product *product)
{
	Stack new_stack = create_stack();
	push_stack(new_stack, product);
	push_stack(depot->stack, new_stack);
}

void push_depot(Depot depot, Product *product)
{
    if (get_count(depot->stack) == 0)
    {
		    insert_new_stack(depot, product);
    }
    else
    {
      Stack stack = (Stack)peek_stack(depot->stack);
       if (get_count(stack) == 3)
       {
         insert_new_stack(depot, product);
       }
       else
       {
          push_stack(stack, product);
       }
    }
}

int get_count(Depot depot)
{
  return get_count(depot->stack);
}

Product* pop_depot(Depot depot)
{
  if (get_count(depot->stack) == 0)
  {
		return 0;
  }

  Product* product;
	Stack stack = (Stack)peek_stack(depot->stack);

	if (get_count(stack) == 1)
  {
		stack = (Stack)pop_stack(depot->stack);
		product = (Product*)pop_stack(stack);
		delete_stack(stack);
		return product;
	}
	return (Product*)pop_stack(stack);
}
