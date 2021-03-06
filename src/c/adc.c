#include "direcciones.h"
#include "adc.h"

void adc_config(void){
	*PCONP|= (1<<12);   			//Prender ADC
	*PCLKSEL0|= (0<<24); 			//selecciona pclock_adc/1
	*PINSEL1|= (1<<14); 			// P0.23 = 01  selecciona AD0.0
	*PINSEL1|= (1<<16);				//P0.24 = 01 selecciona AD0.1
	*AD0CR|= (1<<0);    			//selecciona el canal AD0.0
	*AD0CR|= (1<<1);				//selecciona el canal AD0.1
	*AD0CR|= (1<<21);				//ADC operacional
	*AD0CR|= (1<<16);				//habilita modo burst
	*AD0INTEN&=~(1<<8); 			//si burst=1, AD0INTEN debe estar en 0.
}
