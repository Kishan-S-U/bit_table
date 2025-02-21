#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "../includes/bit_table.h"

static uint8_t* bit_table;
static int table_size;
static int table_search_index;
static bool table_init;


static bit_table_err_t setBit(int N, int K) {

    // Bitwise OR with the mask
    if (table_init == true)
    {
        bit_table[N] = (uint8_t)(bit_table[N] | (1 << (K)));
        return OPERATION_SUCCESS;
    }

    return BIT_TABLE_NOT_INITIALISED;
}

static bit_table_err_t clearBit(int N, int K) {

    // Bitwise AND with the mask
    if (table_init == true)
    {
        bit_table[N] = (uint8_t)(bit_table[N] & (~(1 << (K))));
        return OPERATION_SUCCESS;
    }

    return BIT_TABLE_NOT_INITIALISED;
}

bit_table_err_t clear_table(void)
{
    if (table_init == true)
    {
        memset(bit_table, 0, ((uint32_t)table_size)*sizeof(uint8_t));
        return OPERATION_SUCCESS;
    }
    else
    {
        return BIT_TABLE_NOT_INITIALISED;
    }
}

bit_table_err_t init_bit_table(uint8_t* table, int tableSize)
{
    bit_table = table;
    table_size = (int)(tableSize/8);
    table_search_index = -1;

    if (tableSize % 8 == 0)
    {
        table_init = true;
        return OPERATION_SUCCESS;
    }
    else
    {
        table_init = false;
        return TABLE_SIZE_NOT_SUPPORTED;
    }
}

bit_table_err_t set_table_item(int num)
{
    int bank;
    int pos;

    bank = (int)(num/8);
    pos = num%8;

    if ((pos == 0) & (bank-1 < table_size))
        return setBit(bank-1, pos);
    else if (bank < table_size)
        return setBit(bank, (8 - pos));
    else
        return INDEX_OUT_OF_BOUNDS;
}

bit_table_err_t clear_table_item(int num)
{
    int bank;
    int pos;

    bank = (int)(num/8);
    pos = num%8;

    if ((pos == 0) & (bank-1 < table_size))
        return clearBit(bank-1, pos);
    else if (bank < table_size)
        return clearBit(bank, (8 - pos));
    else
        return INDEX_OUT_OF_BOUNDS;
}

bit_table_err_t search_set_table_item(int* count)
{
    (*count) = 0;
    for (int i=0; i<table_size; i++)
    {
        for (int j=7; j>=0; j--)
        {
            unsigned int mask = (unsigned int)(1 << j);
            if (bit_table[i] & mask)
            {
                (*count)++;
                table_search_index = *count;
                return OPERATION_SUCCESS;
            }
            else
            {
                (*count)++;
            }
        }
    }
    return TABLE_CLEAR;
}

bit_table_err_t next_set_table_item(int* count)
{
    static int bnk = 0;
    static unsigned int mask;

    bnk = (int)(table_search_index/8);
    (*count) = bnk*8;

    if (bnk < 0)
        return BIT_TABLE_NOT_INITIALISED;

    for (int j=7; j>=0; j--)
    {
        mask = (unsigned int)(1 << j);
        if (bit_table[bnk] & mask)
        {
            if ((table_search_index-1) == *count)
            {
                (*count)++;
            }
            else
            {
                (*count)++;
                table_search_index = *count;
                return OPERATION_SUCCESS;
            }
        }
        else
        {
            (*count)++;
        }
    }

    for (int i=bnk+1; i<table_size; i++)
    {
        for (int j=7; j>=0; j--)
        {
            mask = (unsigned int)(1 << j);
            if (bit_table[i] & mask)
            {
                (*count) ++;
                table_search_index = *count;
                return OPERATION_SUCCESS;
            }
            else
            {
                (*count)++;
            }
        }
    }
    return TABLE_CLEAR;
}

bit_table_err_t count_set_table_items(int* count)
{
    count = 0;
    for (int i=0; i<table_size; i++)
    {
        for (int j=7; j>=0; j--)
        {
            unsigned int mask = (unsigned int)(1 << j);
            if (bit_table[i] & mask)
            {
                count ++;
            }
        }
    }

    if (count == 0)
    {
        return TABLE_CLEAR;
    }

    return OPERATION_SUCCESS;
}

bit_table_err_t duplicate_table(uint8_t* buf)
{
    memcpy(buf, bit_table, (uint32_t)table_size);

    return OPERATION_SUCCESS;
}

bit_table_err_t print_table(void)
{
    int count_t = 1;
    for (int i = 0; i < table_size; i++) {

        if ((i%4 == 0) & (i != 0))
        {
            printf("\n");
            count_t++;
        }

        if (i%4 == 0)
        {
            printf("%d  ", count_t);
        }

        for (int j=7; j>=0; j--)
        {
            unsigned int mask = 1 << j;
            printf("%d", (bit_table[i] & mask) ? 1 : 0);
        }
        printf("  ");
    }

    return OPERATION_SUCCESS;
}
