
/* Timer0: contador de segundos
 * Timer1: multiplexado de displays
 * ADC: modulo joystick
 * EINT0: pulsador
 * EINT3 (GPIO): par emisor receptor para pasar de turno
 * setear_jugadores(): inicializa el juego
 * leer_joystick(): lee los valores del ADC conectado al joystick y analiza si se pasa un threshold AD0.0 eje Y, AD0.1 eje X
 * refrescar_rgb(): carga los valores RGB correspondientes
 * buzzer(char a): suena una melodía dependiendo del char enviado
 */
//TODO: Revisar delay en el main para lectura del ADC
//TODO: Revisar frecuencia del ADC
//TODO: Revisar sincronización del Timer1
//TODO: buzzer(char a), la implementacion y discutir el funcionamiento


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

#define adc_threshold_low1  16
#define adc_threshold_low2  500
#define adc_threshold_high1 3500
#define adc_threshold_high2 4080
#define DELAY 1000000


struct jugador{
	unsigned int id;
	unsigned int tiempo;
	unsigned int rgb[3];
}jugador_uno, jugador_dos, *jugador_actual;

static unsigned int mux = 1;


unsigned int tabla[]= {
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

static unsigned int display0 = 0;
static unsigned int display1 = 0;
static unsigned int display2 = 9;
static unsigned int read_joystick = 1;
static unsigned int i = 0;

void setear_jugadores(void);
void leer_joystick(void);
void refrescar_rgb(void);
void buzzer(char a);
void config(void);


int main(void) {

	config();
	//setear_jugadores();


	while(1) {

    if(read_joystick){
    	leer_joystick();
    }else{
      i++;
      if(i > DELAY){
        read_joystick = 1;
        i = 0;
      }
    }

  }
    return 0;
}

void refrescar_rgb(void){
	*FIO2CLR = ((jugador_actual->rgb[0])<<8);
	*FIO2SET = ((~jugador_actual->rgb[0] & 1)<<8);

	*FIO2CLR = ((jugador_actual->rgb[1])<<11);
	*FIO2SET = ((~jugador_actual->rgb[1] & 1)<<11);

	*FIO2CLR = ((jugador_actual->rgb[2])<<12);
	*FIO2SET = ((~jugador_actual->rgb[2] & 1)<<12);
}

void setear_jugadores(void) {
	//jugador_uno
	jugador_uno.id=1;
	jugador_uno.rgb[0]=1;
	jugador_uno.rgb[1]=0;
	jugador_uno.rgb[2]=1;
	jugador_uno.tiempo=900;
	//jugador_dos
	jugador_dos.id=2;
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
	//refrescar_rgb();
}

void leer_joystick(){
	int read_channel0 = 0xfff & (*AD0DR0 >> 4);		//IZQ/DER
	int read_channel1 = 0xfff & (*AD0DR1 >> 4);		//UP/DOWN
			if(read_channel0<adc_threshold_low2){
				uart_enviardato('a');		//Doble velocidad down
        read_joystick = 0;
			}else if ((read_channel0>adc_threshold_low2) && (read_channel0<adc_threshold_low1)){
				uart_enviardato('b');		//Simple velocidad down
        read_joystick = 0;
			}else if (read_channel0>adc_threshold_high2){
				uart_enviardato('c');		//Doble velocidad up
        read_joystick = 0;
			}else if ((read_channel0>adc_threshold_high1) && (read_channel0<adc_threshold_high2)){
				uart_enviardato('d');		//Simple velocidad up
        read_joystick = 0;
			}
			if(read_channel1<adc_threshold_low2){
				uart_enviardato('e');		//Doble velocidad izq
        read_joystick = 0;
			}else if ((read_channel1>adc_threshold_low2) && (read_channel1<adc_threshold_low1)){
				uart_enviardato('f');		//Simple velocidad izq
        read_joystick = 0;
			}else if (read_channel1>adc_threshold_high2){
				uart_enviardato('g');		//Doble velocidad der
        read_joystick = 0;
			}else if ((read_channel1>adc_threshold_high1) && (read_channel1<adc_threshold_high2)){
				uart_enviardato('h');		//Simple velocidad der
        read_joystick = 0;
			}
}

void buzzer (char a){

}

void config(void){
	//Pins
	pins_config();
	//Timer
	//timer_config();
	//ADC
	adc_config();
	//UART
	uart_config();
	//NVIC
	 *ISER0 |= (1<<8);				//Habilita la interrupcion de UART3
  //	*ISER0 |= (1<<1);				//Habilita las interrupciones de Timer0
  //	*ISER0 |= (1<<2);				//Habilita las interrupciones de Timer1
  //	*T1TCR |= (1<<1);
  //	*T1TCR &= ~(1<<1);
  //	*T0TCR |= (1<<1);
  //	*T0TCR &= ~(1<<1);
	//*ISER0 |= (1<<18);				//INTRP por EINT0
	//*ISER0 |= (1<<21);				//INTRP por EINT3 (GPIO)
	//ISER0 |= (1<<22);				//INTRP por ADC
}

void TIMER0_IRQHandler (void){		//Contador de segundos
	if (*T0IR & 1){					//INTRP por MR0
		jugador_actual->tiempo--;
		display0=jugador_actual->tiempo%10;
		display1=(jugador_actual->tiempo/10)%10;
		display2=(jugador_actual->tiempo/100)%10;
	}
	*T0IR |=1;						//Bajar INTRP de T1-MR0
}

void TIMER1_IRQHandler (void){		//Multiplexado
	//TODO REVISAR SINCRONIZACION
	if(*T1IR & 1){
		*FIO1SET = (7<<20);					//Limpiar todos los multiplexados

		if(mux==1){						//Cargar los valores en el puerto
			*FIO2SET = ~tabla[display0];
			*FIO2CLR = tabla[display0];
		}else if(mux==2){
			*FIO2SET = ~tabla[display1];
			*FIO2CLR = tabla[display1];
		}else{
			*FIO2SET = ~tabla[display2];
			*FIO2CLR = tabla[display2];
		}
		*FIO1SET = ~(mux<<20);
		*FIO1CLR = (mux<<20);
		if(mux==4){						//Si mux es 100, resetearlo a 001
			mux=1;
		}else{
			mux = (mux<<1);				//Desplazar el 1 de mux
		}
	}
	*T1IR |= 1;							//Bajar INTRP de T1-MR0
}

void EINT0_IRQHandler(void){			//pulsador
	if(*IO0IntStatF & (1<<6)){
		while((*U3LSR&(1<<5))==0){}		//Esta transmitiendo, entonces esperar
		*U3THR='b';
	}
	*EXTINT |= 1;
}

void EINT3_IRQHandler(void){			//intrp por par emisor-receptor
	if(*IOIntStatus & 1){				//Interrupcion GPIO P0
		if(jugador_actual->id==1){		//Cambiar de turno
			jugador_actual=&jugador_dos;
		}else{
			jugador_actual=&jugador_uno;
		}
		refrescar_rgb();
	}
//	}else if(*IOIntStatus & (1<<2)){	//Interrupcion GPIO P2

//	}
}

void UART3_IRQHandler(void){
	char k=*U3RBR;
	while((*U3LSR&(1<<5))==0){}		//Esta transmitiendo, entonces esperar
	*U3THR='a';
}
/*
void ADC0_IRQHandler(void){
	if (*AD0DR0 & (1<<31)){
	int read = 0xfff & (*AD0GDR >> 4);		//Tomo los 12 bits
		if (read>adc_threshold2){
			while((*U3LSR&(1<<5))==0){}		//Esta transmitiendo, entonces esperar
			*U3THR='a';						//Doble velocidad
		}else if (read>adc_threshold1){
			while((*U3LSR&(1<<5))==0){}		//Esta transmitiendo, entonces esperar
			*U3THR='b';						//Velocidad simple
		}
	}
	*AD0CR |= (1<<24);						//START NOW
}*/
