#include "direcciones.h"

//Pines
unsigned int volatile *const PINSEL0 = (unsigned int*) AddrPINSEL0;
unsigned int volatile *const PINSEL1 = (unsigned int*) AddrPINSEL1;
unsigned int volatile *const PINSEL4 = (unsigned int*) AddrPINSEL4;
unsigned int volatile *const PINMODE0 = (unsigned int*) AddrPINMODE0;

unsigned int volatile *const FIO0DIR = (unsigned int*) AddrFIO0DIR;
unsigned int volatile *const FIO0PIN = (unsigned int*) AddrFIO0PIN;
unsigned int volatile *const FIO0SET = (unsigned int*) AddrFIO0SET;
unsigned int volatile *const FIO0CLR = (unsigned int*) AddrFIO0CLR;

unsigned int volatile *const FIO1DIR = (unsigned int*) AddrFIO1DIR;
unsigned int volatile *const FIO1PIN = (unsigned int*) AddrFIO1PIN;
unsigned int volatile *const FIO1SET = (unsigned int*) AddrFIO1SET;
unsigned int volatile *const FIO1CLR = (unsigned int*) AddrFIO1CLR;

unsigned int volatile *const FIO2DIR = (unsigned int*) AddrFIO2DIR;
unsigned int volatile *const FIO2PIN = (unsigned int*) AddrFIO2PIN;
unsigned int volatile *const FIO2SET = (unsigned int*) AddrFIO2SET;
unsigned int volatile *const FIO2CLR = (unsigned int*) AddrFIO2CLR;
//Timer
unsigned int volatile *const T0MR0 = (unsigned int*) AddrT0MR0;
unsigned int volatile *const T0MR1 = (unsigned int*) AddrT0MR1;
unsigned int volatile *const T0IR = (unsigned int*) AddrT0IR;
unsigned int volatile *const T0MCR = (unsigned int*) AddrT0MCR;
unsigned int volatile *const T0TCR = (unsigned int*) AddrT0TCR;

unsigned int volatile *const T1MR0 = (unsigned int*) AddrT1MR0;
unsigned int volatile *const T1MR1 = (unsigned int*) AddrT1MR1;
unsigned int volatile *const T1IR = (unsigned int*) AddrT1IR;
unsigned int volatile *const T1MCR = (unsigned int*) AddrT1MCR;
unsigned int volatile *const T1TCR = (unsigned int*) AddrT1TCR;
//GPIO
unsigned int volatile *const IO0IntEnF = (unsigned int*) AddrIO0IntEnF;
unsigned int volatile *const IO0IntStatF = (unsigned int*) AddrIO0IntStatF;
unsigned int volatile *const IO0IntClr = (unsigned int*) AddrIO0IntClr;
unsigned int volatile *const IO2IntEnF = (unsigned int*) AddrIO2IntEnF;
unsigned int volatile *const IO2IntStatF = (unsigned int*) AddrIO2IntStatF;
unsigned int volatile *const IO2IntClr = (unsigned int*) AddrIO2IntClr;
unsigned int volatile *const IOIntStatus = (unsigned int*) AddrIOIntStatus;
//ExtINT
unsigned int volatile *const EXTMODE = (unsigned int*) AddrEXTMODE;
unsigned int volatile *const EXTPOLAR = (unsigned int*) AddrEXTPOLAR;
unsigned int volatile *const EXTINT = (unsigned int*) AddrEXTINT;
//ADC
unsigned int volatile *const AD0CR = (unsigned int*) AddrAD0CR;
unsigned int volatile *const AD0DR0 = (unsigned int*) AddrAD0DR0;
unsigned int volatile *const AD0DR1 = (unsigned int*) AddrAD0DR1;
unsigned int volatile *const AD0DR2 = (unsigned int*) AddrAD0DR2;
unsigned int volatile *const AD0DR3 = (unsigned int*) AddrAD0DR3;
unsigned int volatile *const PINMODE1 = (unsigned int*) AddrPINMODE1;
unsigned int volatile *const AD0INTEN = (unsigned int*) AddrAD0INTEN;
unsigned int volatile *const AD0GDR = (unsigned int*) AddrAD0GDR;
//NVIC
unsigned int volatile *const ISER0 = (unsigned int*) AddrISER0;
unsigned int volatile *const ICER0 = (unsigned int*) AddrICER0;
//UART
unsigned int volatile *const U3LCR = (unsigned int*) AddrU3LCR;
unsigned int volatile *const U3DLL = (unsigned int*) AddrU3DLL;
unsigned int volatile *const U3DLM = (unsigned int*) AddrU3DLM;
unsigned int volatile *const U3IER = (unsigned int*) AddrU3IER;
unsigned int volatile *const U3RBR = (unsigned int*) AddrU3RBR;
unsigned int volatile *const U3THR = (unsigned int*) AddrU3THR;
unsigned int volatile *const U3LSR = (unsigned int*) AddrU3LSR;
//Otros
unsigned int volatile *const PCONP = (unsigned int*) AddrPCONP;
unsigned int volatile *const PCLKSEL0 = (unsigned int*) AddrPCLKSEL0;
