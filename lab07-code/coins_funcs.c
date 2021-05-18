#include "coins.h"
// NOTE: Comment out or Uncomment the below functions as you would
// perform `make coins_hybrid` depending on which assembly functions
// you are working on.

// Calculate number of quarters, dimes, nickels, pennies of
// change. Param cents is the number of cents, 0-99. Param coins is a
// pointer to a structure which will have its fields set to the number
// of coins of each type. Returns 0 on success.  If cents is out of
// range, no values are changed and 1 is returned.
int set_coins(int cents, coins_t *coins){
  if(cents < 0 || cents > 99){
    return 1;
  }

  coins->quarters = cents / 25;
  cents = cents % 25;

  coins->dimes = cents / 10;
  cents = cents % 10;

  coins->nickels = cents / 5;
  cents = cents % 5;

  coins->pennies = cents;

  return 0;
}

// Returns the total number of cents in the given coins struct.
int total_coins(coins_t coins){
  int tot = 0;
  tot += coins.quarters * 25;
  tot += coins.dimes * 10;
  tot += coins.nickels * 5;
  tot += coins.pennies;
  return tot;
}
