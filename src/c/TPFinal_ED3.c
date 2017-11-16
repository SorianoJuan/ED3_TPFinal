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
#define adc_threshold_low2  700
#define adc_threshold_high1 3500
#define adc_threshold_high2 4080
#define DELAY 1000000
#define N_MUESTRAS 19
#define FREC_T1 2000


typedef struct jugador{
	unsigned int id;
	unsigned int tiempo;
	unsigned int rgb[3];
}jugador;

static jugador jugador_uno;
static jugador jugador_dos;
static jugador * jugador_actual;

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
static int bub = 0;
static int t_entry=0;
static char buzz=0;
static unsigned int rebote = 0;
static unsigned int eint_rebote = 0;
static unsigned int motor=0;
static unsigned int cont_motor=2000;
static unsigned int fin_partida=0;
static unsigned int inicializado=0;
static unsigned int inicio_partida=0;

void setear_jugadores(void);
void leer_joystick(void);
void refrescar_rgb(void);
void buzzer(char a);
void config(void);
int  mediana(int*, int);


int main(void) {
	config();
    int i = 0;

	while(1) {
		if(buzz){
			buzzer(buzz);
			buzz=0;
		}
        if(inicio_partida){
            buzzer('e');
            for(int i=0;i<10000;i++);
            buzzer('p');
            for(int i=0;i<10000;i++);
            buzzer('f');
            for(int i=0;i<10000;i++);
            buzzer('p');
            for(int i=0;i<10000;i++);
            buzzer('f');
            for(int i=0;i<10000;i++);
            buzzer('e');
            for(int i=0;i<10000;i++);
            buzzer('f');
            inicio_partida=0;
        }
		if(fin_partida){
			buzzer('e');
			for(int i=0;i<10000;i++);
			buzzer('p');
			for(int i=0;i<10000;i++);
			buzzer('f');
			for(int i=0;i<10000;i++);
			buzzer('p');
			for(int i=0;i<10000;i++);
			buzzer('f');
			for(int i=0;i<10000;i++);
			buzzer('e');
			for(int i=0;i<10000;i++);
			buzzer('f');
            //Deshabilitar todas las interrupciones
			*ICER0 = (1<<8);				//Desabilita las interrupciones de UART3
			*ICER0 = (1<<1);				//Deshabilita las interrupciones de Timer0
			//*ICER0 |= (1<<2);				//Desabilita las interrupciones de Timer1
			*ICER0 = (1<<18);				//Desabilita las interrupciones de EINT0
			*ICER0 = (1<<20);				//Desabilita las interrupciones de EINT2
			while (1){      //Bloquearse

			}
		}
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

	*FIO0CLR = ((jugador_actual->rgb[2])<<4);
	*FIO0SET = ((~jugador_actual->rgb[2] & 1)<<4);
}

void setear_jugadores(void) {
	//jugador_uno
	jugador_uno.id=1;
	jugador_uno.rgb[0]=1;
	jugador_uno.rgb[1]=0;
	jugador_uno.rgb[2]=0;
	jugador_uno.tiempo=900;
	//jugador_dos
	jugador_dos.id=2;
	jugador_dos.rgb[0]=0;
	jugador_dos.rgb[1]=0;
	jugador_dos.rgb[2]=1;
	jugador_dos.tiempo=900;
	//turno inicial
	if(!(rand() % 2)){
		jugador_actual=&jugador_uno;
	}else{
		jugador_actual=&jugador_dos;
	}
	refrescar_rgb();
}

void leer_joystick(){
	int channel0[N_MUESTRAS-1];
	int channel1[N_MUESTRAS-1];
	int read_channel0;
	int read_channel1;
	if(bub < N_MUESTRAS){
		channel0[bub] = 0xfff & (*AD0DR0 >> 4);		//IZQ/DER
		channel1[bub] = 0xfff & (*AD0DR1 >> 4);		//UP/DOWN
    	bub++;
    	return;
	}
  bub=0;
  read_channel1 = mediana(channel1, N_MUESTRAS);
  read_channel0 = mediana(channel0, N_MUESTRAS);

	if(read_channel0<adc_threshold_low1){
		uart_enviardato('a');		//Doble velocidad down
        read_joystick = 0;
	}else if ((read_channel0>adc_threshold_low1) && (read_channel0<adc_threshold_low2)){
		uart_enviardato('b');		//Simple velocidad down
        read_joystick = 0;
	}else if (read_channel0>adc_threshold_high2){
		uart_enviardato('c');		//Doble velocidad up
        read_joystick = 0;
	}else if ((read_channel0>adc_threshold_high1) && (read_channel0<adc_threshold_high2)){
		uart_enviardato('d');		//Simple velocidad up
        read_joystick = 0;
	}
	if(read_channel1<adc_threshold_low1){
		uart_enviardato('e');		//Doble velocidad izq
        read_joystick = 0;
	}else if ((read_channel1>adc_threshold_low1) && (read_channel1<adc_threshold_low2)){
		uart_enviardato('f');		//Simple velocidad izq
        read_joystick = 0;
	}else if (read_channel1>adc_threshold_high2+14){
		uart_enviardato('g');		//Doble velocidad der
        read_joystick = 0;
	}else if ((read_channel1>adc_threshold_high1) && (read_channel1<adc_threshold_high2+14)){
		uart_enviardato('h');		//Simple velocidad der
        read_joystick = 0;
	}
}

void buzzer (char a){
	int frec;
	int duracion;
	int x=0;
	int state = 0;
	switch(a){
		case 'p':
			frec = 500;
			duracion = 500;
			break;
		case 'f': //Fin de partida
			frec = 2000;
			duracion = 300;
			break;
		case 'c': //Ficha comida
			frec = 1000;
			duracion = 200;
			break;
		case 'e' : //Error de movimiento
			frec = 400;
			duracion = 500;
			break;
		default:
			return;
	}

	while((x < duracion) && frec){
		if(t_entry){
			t_entry = 0;
			x++;

			if(!(x % (FREC_T1/frec))){
				*FIO0SET = ((state & 1)<<5);
				*FIO0CLR = ((~state & 1)<<5);
				state = ~state;
			}
		}
	}
}

void config(void){
	//Pins
	pins_config();
	setear_jugadores();
	//Timer
	timer_config();
	//ADC
	adc_config();
	//UART
	uart_config();
	//NVIC
	*ISER0 |= (1<<8);				//Habilita la interrupcion de UART3

  	*T0TCR |= (1<<1);
  	*T0TCR &= ~(1<<1);
  	*T0IR |=1;
	//*ISER0 |= (1<<1);

  	*T1TCR |= (1<<1);
  	*T1TCR &= ~(1<<1);
  	*T1IR |=1;
  	*ISER0 |= (1<<2);				//Habilita las interrupciones de Timer1

	*ISER0 |= (1<<18);				//INTRP por EINT0
	*ISER0 |= (1<<20);				//INTRP por EINT2
}

void TIMER0_IRQHandler (void){		//Contador de segundos
	if (*T0IR & 1){					//INTRP por MR0
		if (jugador_actual->tiempo == 0){
			uart_enviardato('r');	//Fin de partida
			fin_partida=1;
			motor = 1;
			cont_motor=6000;
		}else{
			jugador_actual->tiempo--;
			display0=jugador_actual->tiempo%10;
			display1=(jugador_actual->tiempo/10)%10;
			display2=(jugador_actual->tiempo/100)%10;
		}
	}
	*T0IR |=1;						//Bajar INTRP de T1-MR0
}

void TIMER1_IRQHandler (void){		//Multiplexado
	if(!(*ISER0 & (1<<18)) || !(*ISER0 &(1<<20))){//Antirebote
			rebote++;
			if(rebote>600){
				*EXTINT |= (1<<(0+eint_rebote));
				*ISER0 |= (1<<(18+eint_rebote));
				rebote = 0;
			}
	}
	if(motor){//Vibrar motor
		*FIO0CLR = (1<<10);
		cont_motor--;
		if (cont_motor==0){
			motor = 0;
			cont_motor=2000;
			*FIO0SET = (1<<10);
		}
	}
	if(*T1IR & 1){
		t_entry=1;
		*FIO1SET = (7<<20);					//Limpiar todos los multiplexados

		if(mux==1){						//Cargar los valores en el puerto
			*FIO2SET = ~tabla[display0]&(0x7f);
			*FIO2CLR = tabla[display0];
		}else if(mux==2){
			*FIO2SET = ~tabla[display1]&(0x7f);
			*FIO2CLR = tabla[display1];
		}else{
			*FIO2SET = ~tabla[display2]&(0x7f);
			*FIO2CLR = tabla[display2];
		}
		*FIO1SET = ((~mux & 3)<<20);
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
	if(*EXTINT & (1<<0)){
		while((*U3LSR&(1<<5))==0){}		//Esta transmitiendo, entonces esperar
		*U3THR='z';
	}
	eint_rebote = 0;
	*EXTINT |= 1;
	*ICER0 = 1<<18;
}

void EINT2_IRQHandler(void){
	if(!inicializado){//Empezar a contar el tiempo
		inicio_partida=1;               //Tocar melodía
        *T1TCR |= (1<<1);               //Reiniciar Timer
        *T1TCR &= ~(1<<1);
		*T1TCR |= 1;					//Cuando es 1, habilita el contador del Timer y del Prescaler
		*ISER0 |= (1<<1);
        inicializado=1;
	}
	if(*EXTINT & (1<<2)){
		if(jugador_actual->id==1){		//Cambiar de turno
			jugador_actual=&jugador_dos;
		}else{
			jugador_actual=&jugador_uno;
		}
		refrescar_rgb();
		uart_enviardato('p');
		buzz = 'p';
		eint_rebote = 2;
	}
	*EXTINT |= (1<<2);
	*ICER0 = 1<<20;
}

void UART3_IRQHandler(void){
	motor = 1;
	char k=*U3RBR;
		if(k=='e'){//error de movimiento
			buzz='e';
			cont_motor=2000;
		}else if (k=='f'){//final de partida
			fin_partida=1;
			cont_motor=6000;
		}else if (k=='c'){//ficha comida
			buzz='c';
			cont_motor=1000;
		}
}

int mediana(int *array, int muestras){
  int aux;
  int changed = 1;
  while(changed){
    changed = 0;
    for(int i = 0; i < muestras - 2; i++){
      if(array[i] > array[i+1]){
        aux = array[i];
        array[i] = array[i+1];
        array[i+1] = aux;
        changed = 1;
      }
    }
  }
  return array[(muestras-1)/2];
}
