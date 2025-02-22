#ifndef BIT_TABLE_H_INCLUDED
#define BIT_TABLE_H_INCLUDED


typedef enum bit_table_err
{
    OPERATION_SUCCESS = 0,
    TABLE_CLEAR,
    TABLE_SIZE_NOT_SUPPORTED,
    INDEX_OUT_OF_BOUNDS,
} bit_table_err_t;



bit_table_err_t clear_table(uint8_t* bit_table, int table_size);
bit_table_err_t set_table_item(uint8_t* bit_table, int table_size, int num);
bit_table_err_t clear_table_item(uint8_t* bit_table, int table_size, int num);
bit_table_err_t search_set_table_item(uint8_t* bit_table, int table_size, int* count);
bit_table_err_t next_set_table_item(uint8_t* bit_table, int table_size, int* current_idx, int* count);
bit_table_err_t count_set_table_items(uint8_t* bit_table, int table_size, int* count);
bit_table_err_t duplicate_table(uint8_t* buf, uint8_t* bit_table, int table_size);
void print_table(uint8_t* bit_table, int table_size);


#endif // BIT_TABLE_H_INCLUDED
