#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "../includes/bit_table.h"



static bit_table_err_t setBit(uint8_t* bit_table, int N, int K)
{
    bit_table[N] = (uint8_t)(bit_table[N] | (1 << (K)));
    return OPERATION_SUCCESS;
}

static bit_table_err_t clearBit(uint8_t* bit_table, int N, int K)
{
    // Bitwise AND with the mask
    bit_table[N] = (uint8_t)(bit_table[N] & (~(1 << (K))));
    return OPERATION_SUCCESS;
}

bit_table_err_t clear_table(uint8_t* bit_table, int table_size)
{
    static int tableSize;
    tableSize = (int)(table_size/8);
    memset(bit_table, 0, ((uint32_t)tableSize)*sizeof(uint8_t));
    return OPERATION_SUCCESS;
}

bit_table_err_t set_table_item(uint8_t* bit_table, int table_size, int num)
{
    int bank;
    int pos;
    int tableSize;

    tableSize = (int)(table_size/8);
    bank = (int)(num/8);
    pos = num%8;

    if ((pos == 0) & (bank-1 < tableSize))
        return setBit(bit_table, bank-1, pos);
    else if (bank < tableSize)
        return setBit(bit_table, bank, (8 - pos));
    else
        return INDEX_OUT_OF_BOUNDS;
}

bit_table_err_t clear_table_item(uint8_t* bit_table, int table_size, int num)
{
    int bank;
    int pos;
    int tableSize;

    tableSize = (int)(table_size/8);
    bank = (int)(num/8);
    pos = num%8;

    if ((pos == 0) & (bank-1 < tableSize))
        return clearBit(bit_table, bank-1, pos);
    else if (bank < tableSize)
        return clearBit(bit_table, bank, (8 - pos));
    else
        return INDEX_OUT_OF_BOUNDS;
}

bit_table_err_t search_set_table_item(uint8_t* bit_table, int table_size, int* count)
{
    int tableSize;
    tableSize = (int)(table_size/8);

    (*count) = 0;
    for (int i=0; i<tableSize; i++)
    {
        for (int j=7; j>=0; j--)
        {
            unsigned int mask = (unsigned int)(1 << j);
            if (bit_table[i] & mask)
            {
                (*count)++;
                return OPERATION_SUCCESS;
            }
            else
            {
                (*count)++;
            }
        }
    }
    (*count) =  -1;
    return TABLE_CLEAR;
}

bit_table_err_t next_set_table_item(uint8_t* bit_table, int table_size, int* current_idx, int* count)
{
    static int bnk = 0;
    static unsigned int mask;
    int tableSize;
    tableSize = (int)(table_size/8);

    if ((*current_idx) < 0)
        (*current_idx) = 0;

    bnk = (int)((*current_idx)/8);
    (*count) = bnk*8;

    for (int j=7; j>=0; j--)
    {
        mask = (unsigned int)(1 << j);
        if (bit_table[bnk] & mask)
        {
            if (((*current_idx)-1) == *count)
            {
                (*count)++;
            }
            else
            {
                (*count)++;
                (*current_idx) = *count;
                return OPERATION_SUCCESS;
            }
        }
        else
        {
            (*count)++;
        }
    }

    for (int i=bnk+1; i<tableSize; i++)
    {
        for (int j=7; j>=0; j--)
        {
            mask = (unsigned int)(1 << j);
            if (bit_table[i] & mask)
            {
                (*count) ++;
                (*current_idx) = *count;
                return OPERATION_SUCCESS;
            }
            else
            {
                (*count)++;
            }
        }
    }
    (*current_idx) = -1;
    (*count) = -1;
    return TABLE_CLEAR;
}

bit_table_err_t count_set_table_items(uint8_t* bit_table, int table_size, int* count)
{
    int tableSize;
    tableSize = (int)(table_size/8);

    (*count) = 0;
    for (int i=0; i<tableSize; i++)
    {
        for (int j=7; j>=0; j--)
        {
            unsigned int mask = (unsigned int)(1 << j);
            if (bit_table[i] & mask)
            {
                (*count) ++;
            }
        }
    }

    if ((*count) == 0)
    {
        return TABLE_CLEAR;
    }

    return OPERATION_SUCCESS;
}

bit_table_err_t duplicate_table(uint8_t* buf, uint8_t* bit_table, int table_size)
{
    int tableSize;
    tableSize = (int)(table_size/8);
    memcpy(buf, bit_table, (uint32_t)tableSize);

    return OPERATION_SUCCESS;
}

void print_table(uint8_t* bit_table, int table_size)
{
    int tableSize;
    tableSize = (int)(table_size/8);

    int count_t = 1;
    for (int i = 0; i < tableSize; i++) {

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
}
