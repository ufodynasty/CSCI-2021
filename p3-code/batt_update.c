#include "batt.h"
// int set_batt_from_ports(batt_t *batt) {
//   if(BATT_VOLTAGE_PORT < 0) {//If voltage is negative return an error.
//     return 1;
//   }
//   batt->mlvolts = BATT_VOLTAGE_PORT / 2;//coverts raw data to millivolts
//   /*
//     keeping this for when I have to convert my code to assembly
//     batt->percent = batt->mlvolts>3000?batt->mlvolts<3801?(batt->mlvolts - 3000)/8:100:0;//converts millivolts to percent. Established 100 as upper bound and 0 as lower bound.
//   */
//   batt->percent = batt->mlvolts>3000?(batt->mlvolts - 3000)/8:0;//Does ^^ does but doesn't use a nested conditional. Worse code imo.
//   batt->percent = batt->percent<100?batt->percent:100;
//   batt->mode = (BATT_STATUS_PORT & 1<<2)?2:1;//Sets the mode
//   return 0;
// }
// // Uses the two global variables (ports) BATT_VOLTAGE_PORT and
// // BATT_STATUS_PORT to set the fields of the parameter 'batt'.  If
// // BATT_VOLTAGE_PORT is negative, then battery has been wired wrong;
// // no fields of 'batt' are changed and 1 is returned to indicate an
// // error.  Otherwise, sets fields of batt based on reading the voltage
// // value and converting to precent using the provided formula. Returns
// // 0 on a successful execution with no errors. This function DOES NOT
// // modify any global variables but may access global variables.
// //
// // CONSTRAINT: Uses only integer operations. No floating point
// // operations are used as the target machine does not have a FPU.
// // 
// // CONSTRAINT: Limit the complexity of code as much as possible. Do
// // not use deeply nested conditional structures. Seek to make the code
// // as short, and simple as possible. Code longer than 40 lines may be
// // penalized for complexity.
// int set_display_from_batt(batt_t batt, int *display) {
//   int display_bits[11] = {0b0111111,0b0000110,0b1011011,0b1001111,0b1100110,0b1101101,0b1111101,0b0000111,0b1111111,0b1101111,0b0000000};// Look up table for int to 7 segment conversion
//   *display = (batt.percent>89)<<28|(batt.percent>69)<<27|(batt.percent>49)<<26|(batt.percent>29)<<25|(batt.percent>4)<<24|(batt.mode==1)<<23|(batt.mode==1)<<22|(batt.mode==2)<<21|((batt.mode==1)?display_bits[batt.mlvolts/1000]:display_bits[batt.percent/100?1:10])<<14|((batt.mode==1)?display_bits[batt.mlvolts/100%10]:display_bits[batt.percent/10?batt.percent/10%10:10])<<7|((batt.mode==1)?display_bits[batt.mlvolts/10%10+(batt.mlvolts%10>4)]:display_bits[batt.percent%10]); // Could I get extra credit for doing this in 2 lines instead of 65?
//   //^^        ^^ Set bit 28         ^^ set bit 27           ^^ set bit 26       ^^ set bit 25         ^^ set bit 24         ^^ set bit 23     ^^ set bit 22       ^^ set bit 21       ^^ if in v mode, display first didget of v    ^^ check msd of percent:can be 1 or blank   ^^ if in v mode display 2nd didget of v       ^^ if 2 %msds, display didget 2 otherwise display blank  ^^ if in v mode, display lsd                    ^^round 1000ths      ^^ if in % mode, display lsd                
//   return 0;
// }
// Alters the bits of integer pointed to by 'display' to reflect the
// data in struct param 'batt'.  Does not assume any specific bit
// pattern stored at 'display' and completely resets all bits in it on
// successfully completing.  Selects either to show Volts (mode=1) or
// Percent (mode=2). If Volts are displayed, only displays 3 digits
// rounding the lowest digit up or down appropriate to the last digit.
// Calculates each digit to display changes bits at 'display' to show
// the volts/percent according to the pattern for each digit. Modifies
// additional bits to show a decimal place for volts and a 'V' or '%'
// indicator appropriate to the mode. In both modes, places bars in
// the level display as indicated by percentage cutoffs in provided
// diagrams. This function DOES NOT modify any global variables but
// may access global variables. Always returns 0.
// 
// CONSTRAINT: Limit the complexity of code as much as possible. Do
// not use deeply nested conditional structures. Seek to make the code
// as short, and simple as possible. Code longer than 65 lines may be
// penalized for complexity.
int batt_update() {
  batt_t batt = {.mlvolts=-100, .percent=-1, .mode=-1};//initalizes a batt struct
  return set_batt_from_ports(&batt)?1:set_display_from_batt(batt,&BATT_DISPLAY_PORT);
  //     ^^ if init fails return 1     ^^otherwise set display and return 0 (set_display always returns 0)

}
// Called to update the battery meter display.  Makes use of
// set_batt_from_ports() and set_display_from_batt() to access battery
// voltage sensor then set the display. Checks these functions and if
// they indicate an error, does NOT change the display.  If functions
// succeed, modifies BATT_DISPLAY_PORT to show current battery level.
// 
// CONSTRAINT: Does not allocate any heap memory as malloc() is NOT
// available on the target microcontroller.  Uses stack and global
// memory only.