#include "direcciones.h"
#include "adc.h"

void adc_config(void){
	*PCONP|= (1<<12);   			//Prender ADC
	*PCLKSEL0|= (0<<24); 			//selecciona pclock_adc/1
	*PINSEL1|= (1<<14); 			// P0.23 = 01  selecciona AD0.0
	*PINSEL1|= (1<<16);				//P0.24 = 01 selecciona AD0.1
	//*PINSEL1|= (1<<18);				//P0.24 = 01 selecciona AD0.2
	//*PINSEL1|= (1<<20);				//P0.24 = 01 selecciona AD0.3
	*AD0CR|= (1<<0);    			//selecciona el canal AD0.0
	*AD0CR|= (1<<1);				//selecciona el canal AD0.1
	//*AD0CR|= (1<<2);				//selecciona el canal AD0.2
	//*AD0CR|= (1<<3);				//selecciona el canal AD0.3
	*AD0CR|= (1<<21);				//ADC operacional
	//*PINMODE1|= (2<<14); 			//inhabilita resistencias pull up y pull down
	//*AD0INTEN |= 1;				//Habilitar INTRP canal
	*AD0CR|= (1<<16);				//habilita modo burst
	//*AD0CR |= (1<<24);				//Start now
	*AD0INTEN&=~(1<<8); 			//si burst=1, AD0INTEN debe estar en 0.
}
