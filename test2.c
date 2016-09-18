/* 
 * This is a simple PIC 16F648A program that will
 * blink an LED on the RB0 output every half second.
 */

#include <htc.h>  // Header file for PIC processor library files

void delay_10us(unsigned char t);// t*10us delay
void delay_ms(long t);// t ms delay

unsigned char delay; //global used in the Assembly code
// We need "delay" to be a global variable because it will
// be used by a segment of the program that is written in
// assembly language -- see below in function "delay10us".
//
// The C compiler allows assembly language fragments to
// be written in a C language program.  Names of functions
// and variables can be translated into assembly
// language labels.  For example, the C variable name "delay"
// is the same as the assembly language label "_delay".
// However, if "delay" were a local variable in a C function,
// the location of the variable in the machine code is
// difficult to specify in assembly language.  Local
// variables in C functions are implemented in something
// called a "stack", which we'll discuss in lecture later
// in the semester.  On the other hand, global variables
// are assigned distinct and easy to locate memory addresses.
// So we use a global variable for "delay".
//
// We also use a "char" declaration of "delay" rather than
// an "int" declaration because we only want to use up a byte
// of memory rather than multiple bytes.

main(void)
{
TRISB = 0x00; /* All ports of PORTB are outputs */

/* PORTB is an output, and in particular RB0 is an output */
while(1) { /* Turn RB0 on-and-off */
	RB0 = 0;  
	delay_ms(250); // Delay of a quarter-second (= 250 ms)
	RB0 = 1;
 	delay_ms(250); // Delay of a quarter-second (= 250 ms)
} /* End while-loop */
} /* End main */


// The following are functions to create real-time delay.

void delay_10us(unsigned char t)
// Provides t * 10 usecs of delay.
// Max of t is 255 which corresponds to 2550 usecs 
{
delay = t;
/*  Below is an assembly language fragment to 
 *  create a 10 microsecond delay.  Note that in 
 *  this fragment the C global variable "delay" 
 *  is written as "_delay".
 */
#asm
DELAY_10US_1: 
   CLRWDT 
   NOP
   NOP
   NOP
   NOP
   NOP
   NOP 
   DECFSZ  _delay,f 
   GOTO    DELAY_10US_1
#endasm 
} 


void delay_ms(long t) // delays t millisecs
{
long n;
n = t;
do { 
   delay_10us(100);
   } while(--n);
}
