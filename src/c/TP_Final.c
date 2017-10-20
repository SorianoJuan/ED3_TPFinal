#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <cr_section_macros.h>

#include <stdlib.h>

#include "direcciones.h"
#include "pins.h"
#include "timer.h"
#include "adc.h"
#include "uart.h"

struct jugador{
	unsigned int tiempo;
	unsigned int rgb[3];
}jugador_uno, jugador_dos, *jugador_actual;

static unsigned int display0 = 0;
static unsigned int display1 = 0;
static unsigned int display2 = 9;
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

void setear_jugadores(void);
void config(void);

int main(void) {

	setear_jugadores();
	config();

	while(1) {
    }
    return 0;
}

void setear_jugadores(void) {
	//jugador_uno
	jugador_uno.rgb[0]=1;
	jugador_uno.rgb[1]=0;
	jugador_uno.rgb[2]=1;
	jugador_uno.tiempo=900;
	//jugador_dos
	jugador_dos.rgb[0]=0;
	jugador_dos.rgb[1]=0;
	jugador_dos.rgb[2]=1;
	jugador_dos.tiempo=900;
	//turno inicial
	if(rand() % 2){
		jugador_actual=&jugador_uno;
	}else{
		jugador_actual=&jugador_dos;
	}
}

void config(void){
	//Pins
	pins_config();
	//Timer
	timer_config();
	//ADC
	adc_config();
	//UART
	uart_config();
	//NVIC
	*PINSEL4 |= (1<<20);			//10 en posiciones 21 y 20 respectivamente para aceptar interrupciones externas
	*ISER0 |= (1<<8);				//Habilita la interrupcion de UART3
	*ISER0 |= (1<<1);				//Habilita las interrupciones de Timer(el bit 1 es para timer 0)
	*ISER0 |= (1<<18);				//INTRP por EINT0
	*ISER0 |= (1<<21);				//INTRP por EINT3 (GPIO)
}

void TIMER0_IRQHandler (void){
	if (*T0IR & 1){					//INTRP por MR0
		jugador_actual->tiempo--;
		display0=~tabla[jugador_actual->tiempo%10];
		display1=~tabla[(jugador_actual->tiempo/10)%10];
		display2=~tabla[(jugador_actual->tiempo/100)%10];

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
