#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <cr_section_macros.h>

//Pines
#define AddrPINSEL0			0x4002C000
#define AddrFIO0DIR 		0x2009C000
#define AddrFIO0PIN 		0x2009C014
#define AddrFIO0SET 		0x2009C018
#define AddrFIO0CLR 		0x2009C01C
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
unsigned int volatile *const PINSEL0 = (unsigned int*) AddrPINSEL0;
unsigned int volatile *const PINSEL1 = (unsigned int*) AddrPINSEL1;
unsigned int volatile *const PINSEL4 = (unsigned int*) AddrPINSEL4;
unsigned int volatile *const PINMODE0 = (unsigned int*) AddrPINMODE0;
unsigned int volatile *const FIO0DIR = (unsigned int*) AddrFIO0DIR;
unsigned int volatile *const FIO0PIN = (unsigned int*) AddrFIO0PIN;
unsigned int volatile *const FIO0SET = (unsigned int*) AddrFIO0SET;
unsigned int volatile *const FIO0CLR = (unsigned int*) AddrFIO0CLR;
//Timer
unsigned int volatile *const T0MR0 = (unsigned int*) AddrT0MR0;
unsigned int volatile *const T0MR1 = (unsigned int*) AddrT0MR1;
unsigned int volatile *const T0IR = (unsigned int*) AddrT0IR;
unsigned int volatile *const T0MCR = (unsigned int*) AddrT0MCR;
unsigned int volatile *const T0TCR = (unsigned int*) AddrT0TCR;
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
unsigned int volatile *const PINMODE1 = (unsigned int*) AddrPINMODE1;
unsigned int volatile *const AD0INTEN = (unsigned int*) AddrAD0INTEN;
unsigned int volatile *const AD0GDR = (unsigned int*) AddrAD0GDR;
//NVIC
unsigned int volatile *const ISER0 = (unsigned int*) AddrISER0;
//UART
unsigned int volatile *const U3LCR = (unsigned int*) AddrU3LCR;
unsigned int volatile *const U3DLL = (unsigned int*) AddrU3DLL;
unsigned int volatile *const U3DLM = (unsigned int*) AddrU3DLM;
unsigned int volatile *const U3IER = (unsigned int*) AddrU3IER;
unsigned int volatile *const U3RBR = (unsigned int*) AddrU3RBR;
unsigned int volatile *const U3THR = (unsigned int*) AddrU3THR;
unsigned int volatile *const U3U3THR = (unsigned int*) AddrU3THR;
unsigned int volatile *const U3LSR = (unsigned int*) AddrU3LSR;
//Otros
unsigned int volatile *const PCONP = (unsigned int*) AddrPCONP;
unsigned int volatile *const PCLKSEL0 = (unsigned int*) AddrPCLKSEL0;


void init(void);

int main(void) {
init();
        while(1) {
    }
    return 0 ;
}



void init(void){
	//-------
	//Pines
	//-------

	//--------
	//Timer
	//--------
 	*T0MR0;							//MR0
	*T0MR1;							//MR1
	*T0MCR = 0x00000000;			//Borro el registro entero porque no se resetea el HDMP cuando debuggeas un nuevo programa
 	*T0MCR |= (1<<0);				//Genera una interrupción cuando hay match entre MR0 y TC
 	*T0MCR |= (1<<3);				//Genera una interrupción cuando hay match entre MR1 y TC
	*T0MCR |= (1<<4);				//Resetea TC en el match con MR1
	*T0IR  |= (1<<0);				//Limpia la interrupcion de TMR0 MR0
	*T0IR  |= (1<<1);				//Limpia la interrupcion de TMR0 MR1
	*T0TCR |= 1;					//Cuando es 1, habilita el contador del Timer y del Prescaler
	//-------
	//GPIO
	//-------
	*IO0IntEnF |= 1;			//GPIO Interrupt por P0.0
	*IO2IntEnF |= 1;			//GPIO Interrupt por P2.0
	*IO0IntEnF |= (1<<6);		//
	//-------
	//EXTINT
	//-------
	*EXTMODE |= 1;				//0 - Por nivel / 1 - Por flanco
	*EXTINT  |= 1;				//Baja INTRP
	*EXTPOLAR|= 1;				//0 - Por flanco de bajada / 1 - Por flanco de subida
	*EXTINT  |= 1;				//Baja INTRP
	//-------
	//ADC
	//-------
	*PCONP|= (1<<12);   			//Prender ADC
	*PCLKSEL0|= (3<<24); 			//selecciona pclock_adc
	*PINSEL1|= (1<<14); 			// P0.23 = 01  selecciona AD0.0
	*AD0CR|= (1<<0);    			//selecciona el canal AD0.0
	*AD0CR|= (1<<21);				//habilita el ADC
	//*PINMODE1|= (2<<14); 			//inhabilita resistencias pull up y pull down
	*AD0CR|= (1<<16);				//habilita modo burst
	*AD0INTEN&=~(1<<8); 			//si burst=1, AD0INTEN debe estar en 0.
	//--------
	//UART
	//--------
	//*PCONP |= (1<<3);				//Habilitar UART0
	*PCONP |= (1<<25);				//Prender UART3
	*U3LCR |= 11;					//Palabra de 8 bits
	*U3LCR |= (1<<7);				//Activar DLAB (Enable access to division latches para config de BR)
	*U3DLL |= 0xA1; 				//DLL= 161 ->9585 baudios
	*U3DLM |= 0;					//DLM=0
	*U3LCR &=~(1<<7);				//Habilita la interrupcion
	*PINSEL0 |= 0xA;				//p0.0 TX y p0.1 RX
	*PINMODE0 |= 0x8;				//Dejar al aire RX
	*U3IER |= 0x1;					//Setea que se produzca una interrupcion
	//--------
	//NVIC
	//--------
	*PINSEL4 |= (1<<20);			//10 en posiciones 21 y 20 respectivamente para aceptar interrupciones externas
	*ISER0 |= (1<<8);				//Habilita la interrupcion de UART3
	*ISER0 |= (1<<1);				//Habilita las interrupciones de Timer(el bit 1 es para timer 0)
	*ISER0 |= (1<<18);				//INTRP por EINT0
	*ISER0 |= (1<<21);				//INTRP por EINT3 (GPIO)
}
void TIMER0_IRQHandler (void){
	if (*T0IR & 1){					//INTRP por MR0
	}
		*T0IR = (1<<1);				//Bajar INTRP de MR1
}

void EINT0_IRQHandler(void){
	if(*IO0IntStatF & (1<<6)){
	}
	*EXTINT |= 1;
}

void EINT3_IRQHandler(void){
	if(*IOIntStatus & 1){			//Interrupcion GPIO P0

	}else if(*IOIntStatus & (1<<2)){//Interrupcion GPIO P2

	}
}

void UART3_IRQHandler(void){
	char k=*U3RBR;
	while((*U3LSR&(1<<5))==0){}		//Esta transmitiendo, entonces esperar
	*U3THR=k;

}
