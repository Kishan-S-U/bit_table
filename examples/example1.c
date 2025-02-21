#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "../includes/bit_table.h"

int main()
{
    uint8_t tbl[125];
    init_bit_table(&tbl[0], 1000);

    clear_table();

    set_table_item(9);
    set_table_item(43);
    set_table_item(798);
    set_table_item(645);

    print_table();

    int a;
    search_set_table_item(&a);
    printf("\nEarliest set value in table: %d\n", a);
    next_set_table_item(&a);
    printf("Next set value in table: %d\n", a);
    next_set_table_item(&a);
    printf("Next set value in table: %d\n", a);
    next_set_table_item(&a);
    printf("Next set value in table: %d\n", a);

    return 0;
}
