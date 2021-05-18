// test_batt_update.c: testing program for functions in batt_update.c
//
// Mon Feb 22 06:29:10 PM CST 2021 : update to fix incorrect bit
// patterns which were expected on some tests.

#include <string.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "batt.h"

#define PRINT_TEST sprintf(sysbuf,"awk 'NR==(%d+1){P=1;print \"{\"} P==1 && /ENDTEST/{P=0; print \"}\\n---OUTPUT---\"} P==1{print}' %s", __LINE__, __FILE__); \
                   system(sysbuf);

void print_batt(batt_t batt){
  printf("{\n"); 
  printf("  .mlvolts = %d,\n",batt.mlvolts);
  printf("  .percent = %d,\n",batt.percent);
  printf("  .mode    = %d,\n",batt.mode);
  printf("}\n");
}

void print_ports(){
  printf("%-18s : %d\n","BATT_VOLTAGE_PORT", BATT_VOLTAGE_PORT);
  printf("%-18s : %s\n","BATT_STATUS_PORT", bitstr(BATT_STATUS_PORT, CHAR_BITS));
  printf("%-18s : %s\n","BATT_DISPLAY_PORT",bitstr(BATT_DISPLAY_PORT,INT_BITS));
  printf("%-18s : %s\n","index",bitstr_index(INT_BITS));
}

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s <test_name>\n", argv[0]);
    return 1;
  }
  char *test_name = argv[1];
  char sysbuf[1024];

  int *dispint = malloc(sizeof(int)); // used for tests that set the display

  if(0){}

  ////////////////////////////////////////////////////////////////////////////////
  // set_batt_from_ports() tests
  else if( strcmp( test_name, "set_batt_from_ports() 0 V" )==0 ) {
    PRINT_TEST;
    // Check sensor value of 0 and status set for voltage
    BATT_VOLTAGE_PORT = 0;
    BATT_STATUS_PORT  = 0b0000;
    BATT_DISPLAY_PORT = -1;
    batt_t actual = {};            // all 0s
    int ret = set_batt_from_ports(&actual);
    printf("ret: %d\n",ret);
    printf("actual = "); print_batt(actual);
    print_ports();
  } // ENDTEST

  else if( strcmp( test_name, "set_batt_from_ports() 0 P" )==0 ) {
    PRINT_TEST;
    // Check sensor value of 0 and status set for percent
    BATT_VOLTAGE_PORT = 0;
    BATT_STATUS_PORT  = 0b0100;
    BATT_DISPLAY_PORT = -1;
    batt_t actual = {};            // all 0s
    int ret = set_batt_from_ports(&actual);
    printf("ret: %d\n",ret);
    printf("actual = "); print_batt(actual);
    print_ports();
  } // ENDTEST

  else if( strcmp( test_name, "set_batt_from_ports() 7400 V" )==0 ) {
    PRINT_TEST;
    // Check sensor value of 7400 (3.70 V) and status set for voltage
    BATT_VOLTAGE_PORT = 7400;
    BATT_STATUS_PORT  = 0b0000;
    BATT_DISPLAY_PORT = -1;
    batt_t actual = {};            // all 0s
    int ret = set_batt_from_ports(&actual);
    printf("ret: %d\n",ret);
    printf("actual = "); print_batt(actual);
    print_ports();
  } // ENDTEST

  else if( strcmp( test_name, "set_batt_from_ports() 7400 P" )==0 ) {
    PRINT_TEST;
    // Check sensor value of 7400 (3.70 V) and status set for percent
    BATT_VOLTAGE_PORT = 7400;
    BATT_STATUS_PORT  = 0b0100;
    BATT_DISPLAY_PORT = -1;
    batt_t actual = {};            // all 0s
    int ret = set_batt_from_ports(&actual);
    printf("ret: %d\n",ret);
    printf("actual = "); print_batt(actual);
    print_ports();
  } // ENDTEST

  else if( strcmp( test_name, "set_batt_from_ports() STATUS=0b10011001 V" )==0 ) {
    PRINT_TEST;
    // Checks that only bit 2 of BATT_STATUS_PORT is used for
    // determining the Voltage/Percent mode. Bit 2 is 0 but other bits
    // are set in this test
    BATT_VOLTAGE_PORT = 7500;
    BATT_STATUS_PORT  = 0b10011001;
    BATT_DISPLAY_PORT = -1;
    batt_t actual = {};            // all 0s
    int ret = set_batt_from_ports(&actual);
    printf("ret: %d\n",ret);
    printf("actual = "); print_batt(actual);
    print_ports();
  } // ENDTEST

  else if( strcmp( test_name, "set_batt_from_ports() STATUS=0b01110110 P" )==0 ) {
    PRINT_TEST;
    // Checks that only bit 2 of BATT_STATUS_PORT is used for
    // determining the Voltage/Percent mode. Bit 2 is 0 but other bits
    // are set in this test
    BATT_VOLTAGE_PORT = 6277;
    BATT_STATUS_PORT  = 0b01110110;
    BATT_DISPLAY_PORT = -1;
    batt_t actual = {};            // all 0s
    int ret = set_batt_from_ports(&actual);
    printf("ret: %d\n",ret);
    printf("actual = "); print_batt(actual);
    print_ports();
  } // ENDTEST

  else if( strcmp( test_name, "set_batt_from_ports() 7845 P is 100%" )==0 ) {
    PRINT_TEST;
    // Checks that the percentage is set to 100% if voltage port is
    // sufficiently high.
    BATT_VOLTAGE_PORT = 7845;
    BATT_STATUS_PORT  = 0b0100;
    BATT_DISPLAY_PORT = -1;
    batt_t actual = {};            // all 0s
    int ret = set_batt_from_ports(&actual);
    printf("ret: %d\n",ret);
    printf("actual = "); print_batt(actual);
    print_ports();
  } // ENDTEST

  else if( strcmp( test_name, "set_batt_from_ports() 2500 V" )==0 ) {
    PRINT_TEST;
    // Checks a low voltage rating should be 0 percent
    BATT_VOLTAGE_PORT = 2500;
    BATT_STATUS_PORT  = 0b0000;
    BATT_DISPLAY_PORT = -1;
    batt_t actual = {};            // all 0s
    int ret = set_batt_from_ports(&actual);
    printf("ret: %d\n",ret);
    printf("actual = "); print_batt(actual);
    print_ports();
  } // ENDTEST

  else if( strcmp( test_name, "set_batt_from_ports() 6579 P" )==0 ) {
    PRINT_TEST;
    // Checks proper voltage / percent for a mid-range sensor value.
    BATT_VOLTAGE_PORT = 6579;
    BATT_STATUS_PORT  = 0b0100;
    BATT_DISPLAY_PORT = -1;
    batt_t actual = {};            // all 0s
    int ret = set_batt_from_ports(&actual);
    printf("ret: %d\n",ret);
    printf("actual = "); print_batt(actual);
    print_ports();
  } // ENDTEST

  else if( strcmp( test_name, "set_batt_from_ports() 6016 V" )==0 ) {
    PRINT_TEST;
    // Low voltage sensor value should yield 1%
    BATT_VOLTAGE_PORT = 6016;
    BATT_STATUS_PORT  = 0b1011;
    BATT_DISPLAY_PORT = -1;
    batt_t actual = {};            // all 0s
    int ret = set_batt_from_ports(&actual);
    printf("ret: %d\n",ret);
    printf("actual = "); print_batt(actual);
    print_ports();
  } // ENDTEST


  else if( strcmp( test_name, "set_batt_from_ports() 6050 P" )==0 ) {
    PRINT_TEST;
    // Low voltage sensor value, should be nonzero percent
    BATT_VOLTAGE_PORT = 6050;
    BATT_STATUS_PORT  = 0b1100;
    BATT_DISPLAY_PORT = -1;
    batt_t actual = {};            // all 0s
    int ret = set_batt_from_ports(&actual);
    printf("ret: %d\n",ret);
    printf("actual = "); print_batt(actual);
    print_ports();
  } // ENDTEST

  else if( strcmp( test_name, "set_batt_from_ports() FAILS" )==0 ) {
    PRINT_TEST;
    // Negative voltage sensor value should cause a failure and leave
    // the batt_t struct 'actual' unchanged.
    BATT_VOLTAGE_PORT = -7200;
    BATT_STATUS_PORT  = 0b1100;
    BATT_DISPLAY_PORT = -1;
    batt_t actual = {};            // all 0s
    int ret = set_batt_from_ports(&actual);
    printf("ret: %d\n",ret);
    printf("actual = "); print_batt(actual);
    print_ports();
  } // ENDTEST

  ////////////////////////////////////////////////////////////////////////////////
  // set_display_from_batt() tests


  else if( strcmp( test_name, "set_display_from_batt() 0 V" )==0 ) {
    PRINT_TEST;
    // Show 0.0 V
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 0,
      .percent = 0,
      .mode = 1,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST

  else if( strcmp( test_name, "set_display_from_batt() 0 %" )==0 ) {
    PRINT_TEST;
    // Given 0 volts which should also show 0% battery remaining
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 0,
      .percent = 0,
      .mode = 2,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST

  else if( strcmp( test_name, "set_display_from_batt() 3.50 V" )==0 ) {
    PRINT_TEST;
    // Set dispint from the given batt which is in Voltage mode
    // and should result in a bit arrangement showing 3.50 V. 
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 3500,
      .percent = 62,
      .mode = 1,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST

  else if( strcmp( test_name, "set_display_from_batt() 3.507 V" )==0 ) {
    PRINT_TEST;
    // Should show 3.50 V: no rounding associated with the last digit
    // of the voltage reading.
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 3507,
      .percent = 62,
      .mode = 1,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST
  
  else if( strcmp( test_name, "set_display_from_batt() 62 %" )==0 ) {
    PRINT_TEST;
    // Percent mode, show 62 %
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 3500,
      .percent = 62,
      .mode = 2,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST

  else if( strcmp( test_name, "set_display_from_batt() 87 %" )==0 ) {
    PRINT_TEST;
    // Show 87 %
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 3700,
      .percent = 87,
      .mode = 2,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST
  
  else if( strcmp( test_name, "set_display_from_batt() 4.21 V" )==0 ) {
    PRINT_TEST;
    // Show 4.21 Volts
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 4217,
      .percent = 100,
      .mode = 1,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST

  else if( strcmp( test_name, "set_display_from_batt() 100 %" )==0 ) {
    PRINT_TEST;
    // Show 100%, the only case in which the hundreds digit of percent
    // is used.
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 4217,
      .percent = 100,
      .mode = 2,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST

  else if( strcmp( test_name, "set_display_from_batt() level 1" )==0 ) {
    PRINT_TEST;
    // Non-zero level that should show 1 bar in the level meter
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 6151,
      .percent = 9,
      .mode = 2,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST

  else if( strcmp( test_name, "set_display_from_batt() level 2" )==0 ) {
    PRINT_TEST;
    // 30% level is first point at which 2 bars show
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 6480,
      .percent = 30,
      .mode = 2,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST

  else if( strcmp( test_name, "set_display_from_batt() level 3" )==0 ) {
    PRINT_TEST;
    // 56% level is should show 3 bars
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 6900,
      .percent = 56,
      .mode = 1,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST


  else if( strcmp( test_name, "set_display_from_batt() level 4" )==0 ) {
    PRINT_TEST;
    // 89% is highest percentage at which 4 bars will be shown
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 3713,
      .percent = 89,
      .mode = 1,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST

  else if( strcmp( test_name, "set_display_from_batt() level 5" )==0 ) {
    PRINT_TEST;
    // 90% is lowest percentage at which 5 bars will be shown
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 7440,
      .percent = 90,
      .mode = 2,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST

  else if( strcmp( test_name, "set_display_from_batt() level 5 V" )==0 ) {
    PRINT_TEST;
    // 90% is lowest percentage at which 5 bars will be shown
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = 7427,
      .percent = 89,
      .mode = 1,
    };
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST

  else if( strcmp( test_name, "set_display_from_batt() error" )==0 ) {
    PRINT_TEST;
    // Should detect negative voltage and error out
    BATT_VOLTAGE_PORT = -1;
    BATT_STATUS_PORT  = -1;
    BATT_DISPLAY_PORT = -1;
    batt_t batt = {
      .mlvolts = -3421,
      .percent = 0,
      .mode = 2,
    };
    *dispint = -1;        // should not change from -1
    int ret = set_display_from_batt(batt, dispint);
    printf("ret: %d\n",ret);
    printf("%-18s : %s\n%-18s : %s\n",
           "dispint bits", bitstr(*dispint, INT_BITS),
           "index", bitstr_index(INT_BITS));
    printf("\n");  print_ports();  printf("\n");
    BATT_DISPLAY_PORT = *dispint;
    printf("Display based on dispint:\n");
    print_batt_display();
  } // ENDTEST

  ////////////////////////////////////////////////////////////////////////////////
  // batt_update() tests

  else if( strcmp( test_name, "batt_update() 7400 V" )==0 ) {
    PRINT_TEST;
    // call batt_update() with given sensor and status
    BATT_VOLTAGE_PORT = 7400;
    BATT_STATUS_PORT  = 0b0101; // Volts mode
    BATT_DISPLAY_PORT = -1;
    int ret = batt_update();
    printf("ret: %d\n",ret);
    printf("\n");  print_ports();  printf("\n");
    printf("Display based on BATT_DISPLAY_PORT:\n");
    print_batt_display();
  } // ENDTEST

  else if( strcmp( test_name, "batt_update() 7291 P" )==0 ) {
    PRINT_TEST;
    // call batt_update() with given sensor and status
    BATT_VOLTAGE_PORT = 7291;
    BATT_STATUS_PORT  = 0b1011; // Percent mode
    BATT_DISPLAY_PORT = -1;
    int ret = batt_update();
    printf("ret: %d\n",ret);
    printf("\n");  print_ports();  printf("\n");
    printf("Display based on BATT_DISPLAY_PORT:\n");
    print_batt_display();
  } // ENDTEST

  else if( strcmp( test_name, "batt_update() error" )==0 ) {
    PRINT_TEST;
    // call batt_update() with negative voltage reading which should
    // bail out without changing anything.
    BATT_VOLTAGE_PORT = -6421;  // Negative value causes error out
    BATT_STATUS_PORT  = 0b1011; // Percent mode
    BATT_DISPLAY_PORT = -1;
    int ret = batt_update();
    printf("ret: %d\n",ret);
    printf("\n");  print_ports();  printf("\n");
    printf("Display based on BATT_DISPLAY_PORT:\n");
    print_batt_display();
  } // ENDTEST

  else{
    printf("No test named '%s' found\n",test_name);
    return 1;
  }

  free(dispint);
  return 0;
}
