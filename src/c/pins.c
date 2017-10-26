#include "direcciones.h"
#include "pins.h"

void pins_config (void){
	//Pines
	*FIO2DIR |= 0x7F;				//7 segmentos del display
	*FIO1DIR |= (7<<20);			//3 pines de multiplexado
	*FIO2DIR |= 0x700;				//3 salidas de LED RGB
	//GPIO
	*IO0IntEnF |= 1;				//GPIO Interrupt por P0.0
	*IO2IntEnF |= 1;				//GPIO Interrupt por P2.0
	*IO0IntEnF |= (1<<6);			//
	//EXTINT
	*PINSEL4 |= (1<<20);			//10 en posiciones 21 y 20 respectivamente para aceptar interrupciones externas
	*EXTMODE |= 1;					//0 - Por nivel / 1 - Por flanco
	*EXTINT  |= 1;					//Baja INTRP
	*EXTPOLAR|= 1;					//0 - Por flanco de bajada / 1 - Por flanco de subida
	*EXTINT  |= 1;					//Baja INTRP
}
