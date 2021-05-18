#ifndef COINS_H
#define COINS_H

typedef struct {         // Type for collections of coins
  char quarters;
  char dimes;
  char nickels;
  char pennies;
} coins_t;
// coint_t has the following memory layout and argument passing
// properties:
//
// |          | Pointer | Packed | Packed |
// |          |  Memory | Struct | Struct |
// | Field    |  Offset | Arg#   | Bits   |
// |----------+---------+--------+--------|
// | quarters |      +0 | #1     | 0-7    |
// | dimes    |      +1 | #1     | 8-15   |
// | nickels  |      +2 | #1     | 16-23  |
// | pennies  |      +3 | #1     | 24-31  |
//
// Since the entire struct is less that 64-bits, it is passed in a
// single argument register on 64-bit systems when passed as a value
// such as in the below total_coins() function.

int set_coins(int cents, coins_t *coins);
int total_coins(coins_t coins);

#endif
