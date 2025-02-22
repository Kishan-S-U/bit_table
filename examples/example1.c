#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../includes/bit_table.h"

int main()
{
    char tbl[125];
    const int tbl_size = 1000;
    int a, cur_idx=0;
    // initialise all table contents to zero
    clear_table(&tbl[0], tbl_size);

    // set a specific bit in the table
    set_table_item(&tbl[0], tbl_size, 8);
    set_table_item(&tbl[0], 43, tbl_size);

    set_table_item(&tbl[0], tbl_size, 111);
    set_table_item(&tbl[0], tbl_size, 397);

    // print the table on console
    print_table(&tbl[0], tbl_size);

    // get total number of set items in the table
    count_set_table_items(&tbl[0], tbl_size, &a);
    printf("\nnumber of set items = %d\n", a);

    // get one set_item from the table and its index; passing this index again will begin search from this index
    next_set_table_item(&tbl[0], tbl_size, &cur_idx, &a);
    printf("\nEarliest set value in table: %d\n", a);

    next_set_table_item(&tbl[0], tbl_size, &cur_idx, &a);
    printf("\nEarliest set value in table: %d\n", a);

    next_set_table_item(&tbl[0], tbl_size, &cur_idx, &a);
    printf("\nEarliest set value in table: %d\n", a);

    next_set_table_item(&tbl[0], tbl_size, &cur_idx, &a);
    printf("\nEarliest set value in table: %d\n", a);

    return 0;
}
