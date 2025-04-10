# Bit Table

### What is a BIT_TABLE ?
This is a mechanism used to maintain a record of something.
Example: Maintaining attendance

| Employee Name | Attendance Status |
|---|---|
| Person_one | Attended |
| Person_two | Business Leave |
| Person_three | Paid_Leave |
| Person_four | Unpaid_Leave |
| So on... |  |

The same table can be written like this,
There are four types of attendance_states in this example;
| Attendance State | Bit Value |
|---|---|
| Attended | 00 | 
| Business Leave | 01 |
| Paid Leave | 10 |
| Unpaid Leave | 11 |

This is bit table. 
In terms of memory, 1000 employees attendance data can be stored in 250 bytes.

### Why use a BIT_TABLE ?
Consider a scenario where we need to maintain a record of 1000 sensors. These sensors are independent in their operation, and reports its state to the main MCU. We need a method to maintain the states of these sensors in one place, that is where bit_table plays its role. This is one method to maintain a large or small record of anything in an embedded system [with low computational power and memory]. 

### Current library capabilities and future release plans
Currently, this library is capable of enabling control over a single-bit table. In future release, more features with better approach will be implemented.

### Run examples
1. Pull this repository or download to the local machine
2. Download and install a C-Compiler [GCC recommended]
3. Navigate to 'bit_table/output_files' folder and run examples. [This folder contains executable files].

Note: These example programs are present in 'bit_table/examples' folder. 

### Important Note
The size of a bit_table should be in a multiple of 8. Otherwise, a bit_table will not be created and parsed properly.