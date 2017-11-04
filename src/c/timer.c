#include "direcciones.h"
#include "timer.h"

void timer_config (void){
	//Timer0
 	*T0MR0 = 25000000;				//MR0 Contando 1 segundo para displays
	*T0MCR = 0x00000000;
 	*T0MCR |= (1<<0);				//Genera una interrupción cuando hay match entre MR0 y TC
	*T0MCR |= (1<<1);				//Resetea TC en el match con MR1
	*T0IR  |= (1<<0);				//Limpia la interrupcion de TMR0 MR0
	*T0TCR |= 1;					//Cuando es 1, habilita el contador del Timer y del Prescaler
	*T0TCR |= (1<<1);
	*T0TCR |= ~(1<<1);
	//Timer1
	*T1MR0 = 500000;				//MR0 Contando 20ms para multiplexado de displays
	*T1MCR = 0x00000000;
 	*T1MCR |= (1<<0);				//Genera una interrupción cuando hay match entre MR0 y TC
	*T1MCR |= (1<<1);				//Resetea TC en el match con MR1
	*T1IR  |= (1<<0);				//Limpia la interrupcion de TMR0 MR0
	*T1TCR |= 1;					//Cuando es 1, habilita el contador del Timer y del Prescaler
	*T1TCR |= (1<<1);
	*T1TCR |= ~(1<<1);
}
