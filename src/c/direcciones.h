#ifndef DIRECCIONES_H
#define DIRECCIONES_H

//Pines
#define AddrPINSEL0			0x4002C000
#define AddrFIO0DIR 		0x2009C000
#define AddrFIO0PIN 		0x2009C014
#define AddrFIO0SET 		0x2009C018
#define AddrFIO0CLR 		0x2009C01C

#define AddrFIO1DIR 		0x2009C020
#define AddrFIO1PIN 		0x2009C034
#define AddrFIO1SET 		0x2009C038
#define AddrFIO1CLR 		0x2009C03C

#define AddrFIO2DIR 		0x2009C040
#define AddrFIO2PIN 		0x2009C054
#define AddrFIO2SET 		0x2009C058
#define AddrFIO2CLR 		0x2009C05C

#define AddrFI21DIR 		0x2009C040
#define AddrFI21PIN 		0x2009C054
#define AddrFI21SET 		0x2009C058
#define AddrFI21CLR 		0x2009C05C

#define AddrPINMODE0 		0x4002C040	//Para UART3
#define AddrPINSEL1 		0x4002C004
#define AddrPINSEL4			0x4002C010
//Timer
#define AddrT0MR0  			0x40004018	//Match Register 0. Se habilita vía MCR para resetear el TC, parar el TC y PC y/o generar una INTRP cada vez que MR0=TC
#define AddrT0MR1   		0x4000401C	//Match Register 1. Ver MR0.
#define AddrT0IR    		0x40004000	//Interrupt Register. Se escribe para limpiar INTRP. Se puede leer para identificar INTRP pendientes (8 posibles)
#define AddrT0MCR   		0x40004014	//Match Control Register. Controla si se genera una interrupcion y si se resetea el TC cuando ocurre un match.
#define AddrT0TCR  			0x40004004	//Timer Control Register. Controla la funcion del TC. El TC se puede deshabilitar o resetear por medio del TCR.
#define AddrT0CCR			0x40004028	//Capture Control Register. Controla que flancos de input de captura cargan los Capture Registers y si se genera una INTRP.
#define AddrT0CR0			0x4000402C	//Capture Register 0. CR0 se carga con el valor de TC cuando ocurre un evento en CAPn.0 (CAP0.0 o CAP1.0 respectivamente).
#define AddrT0EMR			0x4000403C	//External Match Register. Controla los pines externos de match MATn.0-3.
#define T0CTCR				0x40004070	//Count Control Register. Selecciona entre modos Timer y Counter y en modo Counter selecciona la señal y los flancos.

#define AddrT1MR0  			0x40008018 //
#define AddrT1MR1   		0x4000801C //
#define AddrT1IR    		0x40008000 //
#define AddrT1MCR   		0x40008014 //
#define AddrT1TCR  			0x40008004 //
#define AddrT1CCR			0x40008028 //
#define AddrT1CR0			0x4000802C //
#define AddrT1EMR			0x4000803C //
#define T1CTCR				0x40008070 //
//GpioInt
#define AddrIO0IntEnF		0x40028094
#define AddrIO0IntStatF 	0x40028088
#define AddrIO0IntClr		0x4002808C
#define AddrIO2IntEnF		0x400280B4
#define AddrIO2IntStatF 	0x400280A8
#define AddrIO2IntClr		0x400280AC
#define AddrIOIntStatus		0x40028080
//ExtINT
#define AddrISER0   		0xE000E100
#define AddrEXTMODE 		0x400FC148
#define AddrEXTPOLAR 		0x400FC14C
#define AddrEXTINT 			0x400FC140
//ADC
#define AddrAD0CR 			0x40034000
#define AddrAD0DR0 			0x40034010
#define AddrPINMODE1 		0x4002C044
#define AddrAD0INTEN  		0x4003400C
#define AddrAD0GDR 			0x40034004
//UART
#define AddrU3LCR 			0x4009C00C	//
#define AddrU3DLL 			0x4009C000	//
#define AddrU3DLM 			0x4009C004	//
#define AddrU3IER 			0x4009C004	//
#define AddrU3RBR  			0x4009C000	//
#define AddrU3THR  			0x4009C000	//
#define AddrU3LSR 			0x4009C014	//
//NVIC
#define AddrISER0  			0xE000E100
//Otros
#define AddrPCLKSEL0		0x400FC1A8	//Para ADC
#define AddrPCONP			0x400FC0C4	//Prender UART3



//Pines
extern unsigned int volatile *const PINSEL0;
extern unsigned int volatile *const PINSEL1;
extern unsigned int volatile *const PINSEL4;
extern unsigned int volatile *const PINMODE0;

extern unsigned int volatile *const FIO0DIR;
extern unsigned int volatile *const FIO0PIN;
extern unsigned int volatile *const FIO0SET;
extern unsigned int volatile *const FIO0CLR;

extern unsigned int volatile *const FIO1DIR;
extern unsigned int volatile *const FIO1PIN;
extern unsigned int volatile *const FIO1SET;
extern unsigned int volatile *const FIO1CLR;

extern unsigned int volatile *const FIO2DIR;
extern unsigned int volatile *const FIO2PIN;
extern unsigned int volatile *const FIO2SET;
extern unsigned int volatile *const FIO2CLR;
//Timer
extern unsigned int volatile *const T0MR0;
extern unsigned int volatile *const T0MR1;
extern unsigned int volatile *const T0IR;
extern unsigned int volatile *const T0MCR;
extern unsigned int volatile *const T0TCR;

extern unsigned int volatile *const T1MR0;
extern unsigned int volatile *const T1MR1;
extern unsigned int volatile *const T1IR;
extern unsigned int volatile *const T1MCR;
extern unsigned int volatile *const T1TCR;
//GPIO
extern unsigned int volatile *const IO0IntEnF;
extern unsigned int volatile *const IO0IntStatF;
extern unsigned int volatile *const IO0IntClr;
extern unsigned int volatile *const IO2IntEnF;
extern unsigned int volatile *const IO2IntStatF;
extern unsigned int volatile *const IO2IntClr;
extern unsigned int volatile *const IOIntStatus;
//ExtINT
extern unsigned int volatile *const EXTMODE;
extern unsigned int volatile *const EXTPOLAR;
extern unsigned int volatile *const EXTINT;
//ADC
extern unsigned int volatile *const AD0CR;
extern unsigned int volatile *const AD0DR0;
extern unsigned int volatile *const PINMODE1;
extern unsigned int volatile *const AD0INTEN;
extern unsigned int volatile *const AD0GDR;
//NVIC
extern unsigned int volatile *const ISER0;
//UART
extern unsigned int volatile *const U3LCR;
extern unsigned int volatile *const U3DLL;
extern unsigned int volatile *const U3DLM;
extern unsigned int volatile *const U3IER;
extern unsigned int volatile *const U3RBR;
extern unsigned int volatile *const U3THR;
extern unsigned int volatile *const U3U3THR;
extern unsigned int volatile *const U3LSR;
//Otros
extern unsigned int volatile *const PCONP;
extern unsigned int volatile *const PCLKSEL0;

#endif //DIRECCIONES_H
