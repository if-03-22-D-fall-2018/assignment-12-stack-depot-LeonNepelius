#ifndef SPL_DEPOT_H
#define SPL_DEPOT_H

#include "stack.h"

struct Product
{
    int serial_no;
};

typedef struct DepotImplementation* Depot;

Depot create_depot();

void delete_depot(Depot depot);

void push_depot(Depot depot, Product *product);

int get_count(Depot depot);

Product* pop_depot(Depot depot);

#endif
