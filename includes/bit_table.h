#ifndef BIT_TABLE_H_INCLUDED
#define BIT_TABLE_H_INCLUDED


typedef enum bit_table_err
{
    OPERATION_SUCCESS = 0,
    TABLE_CLEAR,
    TABLE_SIZE_NOT_SUPPORTED,
    INDEX_OUT_OF_BOUNDS,
    BIT_TABLE_NOT_INITIALISED,


} bit_table_err_t;



bit_table_err_t clear_table(void);
bit_table_err_t init_bit_table(uint8_t* table, int tableSize);
bit_table_err_t set_table_item(int num);
bit_table_err_t clear_table_item(int num);
bit_table_err_t search_set_table_item(int* count);
bit_table_err_t next_set_table_item(int* count);
bit_table_err_t count_set_table_items(int* count);
bit_table_err_t duplicate_table(uint8_t* buf);
bit_table_err_t print_table(void);


#endif // BIT_TABLE_H_INCLUDED
