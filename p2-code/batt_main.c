// batt_sim.c: DO NOT MODIFY
//
// Battery meter simulator main program and supporting functions. Read
// voltage sensor value and mode (volts or percent) from the command
// line and show the results of running functions from batt_update.c
// on the screen.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "batt.h"
//                         3210
#define VOLTAGE_FLAG 0b01111001     // bit 2 is 0 but others may be set
#define PERCENT_FLAG 0b10010101     // bit 2 is 1 but others may be set

int main(int argc, char **argv){

  if(argc < 3){                 
    printf("usage: %s {voltage_val} {V | P}\n",argv[0]);
    printf("  arg1 voltage_val: integer, units of 0.001 volts \n");
    printf("  arg2 V or P: Voltage or Percent display\n");
    return 0;
  }
  BATT_VOLTAGE_PORT = atoi(argv[1]);
  printf("BATT_VOLTAGE_PORT set to: %u\n", BATT_VOLTAGE_PORT);

  // unsigned int batt_max = 1000 * 128;
  // if(BATT_VOLTAGE_PORT > batt_max){
  //   printf("Voltage value %u exceeds max %u\n",BATT_VOLTAGE_PORT,batt_max);
  //   return 1;
  // }

  if(argv[2][0]=='V' || argv[2][0]=='v'){
    BATT_STATUS_PORT |= VOLTAGE_FLAG;
  }
  else if(argv[2][0]=='P' || argv[2][0]=='p'){
    BATT_STATUS_PORT |= PERCENT_FLAG;
  }
  else{
    printf("Unknown display mode: '%s'\n",argv[2]);
    printf("Should be 'V' or 'P'\n");
    return 1;
  }
  printf("BATT_STATUS_PORT  set to: 0x%02X\n",BATT_STATUS_PORT);

  printf("\n");

  batt_t batt = {.mlvolts=-100, .percent=-1, .mode=-1};
  int result = set_batt_from_ports(&batt);
  printf("result = set_batt_from_ports( &batt );\n");
  printf("result: %d\n",result);
  printf("batt = {\n"); 
  printf("  .mlvolts = %d\n", batt.mlvolts);
  printf("  .percent = %d\n", batt.percent);
  printf("  .mode    = %d\n", batt.mode);
  printf("}\n");

  printf("\n");

  int display = 0;
  result = set_display_from_batt(batt, &display);
  printf("result = set_display_from_batt(batt, &display);\n");
  printf("result: %d\n", result);
  printf("display is\n");
  printf("bits:  %s\n",bitstr(display, INT_BITS));
  printf("index: %s\n",bitstr_index(INT_BITS));

  // print_intbits(display);

  printf("\n");

  result = batt_update();
  printf("result = batt_update();\n");
  printf("result: %d\n", result);
  printf("BATT_DISPLAY_PORT is\n");
  printf("bits:  %s\n",bitstr(BATT_DISPLAY_PORT, INT_BITS));
  printf("index: %s\n",bitstr_index(INT_BITS));

  printf("\n");
  printf("Battery Meter Display:\n");
  print_batt_display();

  return 0;
}
