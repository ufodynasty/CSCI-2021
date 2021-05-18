#ifndef BATT_H
#define BATT_H 1

// size in bits of some types
#define INT_BITS   (sizeof(int)*8)
#define SHORT_BITS (sizeof(short)*8)
#define CHAR_BITS  (sizeof(char)*8)

////////////////////////////////////////////////////////////////////////////////
// battery meter structs/functions

// Breaks battery stats down into constituent parts
typedef struct{
  short mlvolts;     // voltage read from port, units of 0.001 Volts (milli Volts)
  char  percent;     // percent full converted from voltage
  char  mode;        // 1 for volts, 2 for percent
} batt_t;

// Functions to implement for battery problem
int set_batt_from_ports(batt_t *batt);
int set_display_from_batt(batt_t batt, int *display);
int batt_update();

////////////////////////////////////////////////////////////////////////////////
// batt_sim.c structs/functions; do not modify

extern short BATT_VOLTAGE_PORT;
// Sensor tied to the battery, provides a measure of voltage in units
// of 0.0005 volts (half milli volts). The sensor can sense a wide
// range of voltages including negatives but the batteries being
// measured are Full when 3.8V (7600 sensor value) or above is read
// and Empty when 3.0V (6000 sensor value) or lower is read.

extern unsigned char BATT_STATUS_PORT;
// The bit at index 2 indicates whether display should be in Volts (0)
// or Percent (1). C code should only read this port. Tied to a user
// button which will toggle the bit. Other bits in this char may be
// set to indicate the status of other parts of the meter and should
// be ignored: ONLY BIT 2 BIT MATTERS.

extern int BATT_DISPLAY_PORT;
// Controls battery meter display. Readable and writable. C code
// should mostly write this port with a sequence of bits which will
// light up specific elements of the LCD panel.


// Show the battery display as ASCII on the screen; provided in the
// batt_sim.c file.
void print_batt_display();

// Utilities to show the bits of an integer.
void showbits(int x);
void print_intbits(int x);
char *bitstr(int x, int bits);
char *bitstr_index(int bits);

//extern char *bit_indexes;

#endif
