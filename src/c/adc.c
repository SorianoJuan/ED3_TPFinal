#include "direcciones.h"
#include "adc.h"

void adc_config(void){
	*PCONP|= (1<<12);   			//Prender ADC
	*PCLKSEL0|= (3<<24); 			//selecciona pclock_adc
	*PINSEL1|= (1<<14); 			// P0.23 = 01  selecciona AD0.0
	*AD0CR|= (1<<0);    			//selecciona el canal AD0.0
	*AD0CR|= (1<<21);				//habilita el ADC
	//*PINMODE1|= (2<<14); 			//inhabilita resistencias pull up y pull down
	*AD0CR|= (1<<16);				//habilita modo burst
	*AD0INTEN&=~(1<<8); 			//si burst=1, AD0INTEN debe estar en 0.
}
