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

#define AddrFIO1DIR 		0x2009C020
#define AddrFIO1PIN 		0x2009C034
#define AddrFIO1SET 		0x2009C038
#define AddrFIO1CLR 		0x2009C03C

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


void inicializar(void);
void config(void);

static unsigned int display0 = 0;
static unsigned int display1 = 0;
static unsigned int display2 = 9;
static unsigned int tiempo = 900;
static unsigned int mux = 1;

static unsigned int tabla[]= {
					0x000000c0,		//0 - 11000000
			  	  	0x000000f9,		//1 - 11111001
					0x000000a4,		//2 - 10100100
					0x000000b0,		//3 - 10110000
					0x00000099,		//4 - 10011001
					0x00000012,		//5 - 00010010
					0x00000082,		//6 - 10000010
					0x000000f8,		//7 - 11111000
					0x00000080,		//8 - 10000000
					0x00000090};	//9 - 10010000


int main(void) {

config();

inicializar();

        while(1) {
    }
    return 0 ;
}



void config(void){
	//-------
	//Pines
	//-------
	*FIO2DIR |= 0x7F;				//7 segmentos del display
	*FIO1DIR |= (7<<20);			//3 pines de multiplexado
	*FIO2DIR |= 0x700;				//3 salidas de LED RGB
	//--------
	//Timer
	//--------
	//Timer0
 	*T0MR0 = 25000000;				//MR0 Contando 1 segundo para displays
	*T0MCR = 0x00000000;
 	*T0MCR |= (1<<0);				//Genera una interrupción cuando hay match entre MR0 y TC
	*T0MCR |= (1<<1);				//Resetea TC en el match con MR1
	*T0IR  |= (1<<0);				//Limpia la interrupcion de TMR0 MR0
	*T0TCR |= 1;					//Cuando es 1, habilita el contador del Timer y del Prescaler
	//Timer1
	*T1MR0 = 500000;				//MR0 Contando 20ms para multiplexado de displays
	*T1MCR = 0x00000000;
 	*T1MCR |= (1<<0);				//Genera una interrupción cuando hay match entre MR0 y TC
	*T1MCR |= (1<<1);				//Resetea TC en el match con MR1
	*T1IR  |= (1<<0);				//Limpia la interrupcion de TMR0 MR0
	*T1TCR |= 1;					//Cuando es 1, habilita el contador del Timer y del Prescaler
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
void inicializar(void){

}

void TIMER0_IRQHandler (void){
	if (*T0IR & 1){					//INTRP por MR0
		tiempo--;
		display0=~tabla[tiempo%10];
		display1=~tabla[(tiempo/10)%10];
		display2=~tabla[(tiempo/100)%10];

	}
		*T0IR = (1<<1);				//Bajar INTRP de MR1
}

void TIMER1_IRQHandler (void){
	//TODO REVISAR SINCRONIZACION
	*FIO1CLR |= 7;					//Limpiar todos los multiplexados

	if(mux==1){						//Cargar los valores en el puerto
		*FIO2SET |= display0;
		*FIO2CLR |= display0;
	}else if(mux==2){
		*FIO2SET |= display1;
		*FIO2CLR |= display1;
	}else{
		*FIO2SET |= display2;
		*FIO2CLR |= display2;
	}

	if(mux==4){						//Si mux es 100, resetearlo a 001
		mux=1;
	}else
	{
		mux = (mux<<1);				//Desplazar el 1 de mux
	}
	*FIO1SET |= mux;
	*FIO1CLR &= ~mux;
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
