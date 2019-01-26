#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "shortcut.h"
#include "test_depot.h"
#include "depot.h"
#include "stack.h"

// Stack Tests
TEST(create_stack)
{
	Stack stack = create_stack ();
	ASSERT_FALSE(stack == 0, "Stack has to be created");
	delete_stack(stack);
	ASSERT_EQUALS(true, memcheck_validate());
}

TEST(add_items_to_stack)
{
	Stack stack = create_stack ();

	Product products[] = {
        {1},
        {2},
        {3}
    };
	push_stack (stack, &products[0]);
	push_stack (stack, &products[1]);
	push_stack (stack, &products[2]);

	ASSERT_EQUALS(get_count(stack), 3);

	delete_stack(stack);
	ASSERT_EQUALS(true, memcheck_validate());
}

TEST(get_items_from_stack)
{
	Stack stack = create_stack ();

	Product products[] = {
        {1},
        {2},
        {3}
    };
	push_stack (stack, &products[0]);
	push_stack (stack, &products[1]);
	push_stack (stack, &products[2]);

	ASSERT_EQUALS(((Product*)pop_stack (stack))->serial_no, 3);
	ASSERT_EQUALS(((Product*)pop_stack (stack))->serial_no, 2);

	ASSERT_EQUALS(((Product*)peek_stack (stack))->serial_no, 1);
	ASSERT_EQUALS(get_count(stack), 1);

	ASSERT_EQUALS(((Product*)pop_stack (stack))->serial_no, 1);
	ASSERT_EQUALS(get_count(stack), 0);

	delete_stack(stack);
	ASSERT_EQUALS(true, memcheck_validate());
}

// Depot tests
TEST(create_depot)
{
	Depot depot = create_depot();
	ASSERT_FALSE(depot == 0, "Depot has to be created");
	delete_depot(depot);
	ASSERT_EQUALS(true, memcheck_validate());
}

TEST(fill_depot)
{
	Depot depot = create_depot();

	Product products[] = {
        {1},
        {2},
        {3},
		{4}
    };

	ASSERT_EQUALS(get_count(depot), 0);

	push_depot(depot, &products[0]);
	ASSERT_EQUALS(get_count(depot), 1);
	push_depot(depot, &products[1]);
	ASSERT_EQUALS(get_count(depot), 1);
	push_depot(depot, &products[2]);
	ASSERT_EQUALS(get_count(depot), 1);
	push_depot(depot, &products[3]);
	ASSERT_EQUALS(get_count(depot), 2);

	delete_depot(depot);
	ASSERT_EQUALS(true, memcheck_validate());
}

TEST(use_depot)
{
	Depot depot = create_depot();

	Product products[] = {
        {1},
        {2},
        {3},
		{4},
		{5},
		{6},
		{7}
    };

	for (int i = 0; i < 7; i++){
		push_depot(depot, &products[i]);
	}
	ASSERT_EQUALS(get_count(depot), 3);

	for (int j = 6; j >= 0; j--){
		Product *p = pop_depot(depot);
		ASSERT_EQUALS(p->serial_no, j+1);
		if (j == 4){
			ASSERT_EQUALS(get_count(depot), 2);
		}
		if (j == 2){
			ASSERT_EQUALS(get_count(depot), 1);
		}
	}
	ASSERT_EQUALS(get_count(depot), 0);

	push_depot(depot, &products[0]);
	push_depot(depot, &products[1]);
	push_depot(depot, &products[2]);
	push_depot(depot, &products[3]);
	pop_depot(depot);
	push_depot(depot, &products[4]);
	ASSERT_EQUALS(get_count(depot), 2);
	ASSERT_EQUALS(((Product*)pop_depot(depot))->serial_no, 5);
	ASSERT_EQUALS(get_count(depot), 1);

	delete_depot(depot);
	ASSERT_EQUALS(true, memcheck_validate());
}
