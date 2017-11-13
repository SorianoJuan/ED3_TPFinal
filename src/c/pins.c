#include "direcciones.h"
#include "pins.h"

void pins_config (void){
	//Pines
	*FIO2DIR = 0x7F;				//7 segmentos del display
	*FIO1DIR = (7<<20);				//3 pines de multiplexado
	*FIO0DIR |= (3<<4);				//Buzzer + Blue
	*FIO2DIR |= 0x900;				//3 salidas de LED RG sin B
	*FIO0DIR |= (1<<10);				//Motor
	*FIO0SET = (1<<10);				//Apagar motor
	//EXTINT 0
	*PINSEL4 |= (1<<20);			//10 en posiciones 21 y 20 respectivamente para aceptar interrupciones externas
	*EXTMODE |= 1;					//0 - Por nivel / 1 - Por flanco
	*EXTINT  |= 1;					//Baja INTRP
	*EXTPOLAR &= ~1;				//0 - Por flanco de bajada / 1 - Por flanco de subida
	*EXTINT  |= 1;					//Baja INTRP
	//EXTINT 2
	*PINSEL4 |= (1<<24);			//10 en posiciones 21 y 20 respectivamente para aceptar interrupciones externas
	*EXTMODE |= (1<<2);				//0 - Por nivel / 1 - Por flanco
	*EXTINT  |= (1<<2);				//Baja INTRP
	*EXTPOLAR &= (~1<<2);			//0 - Por flanco de bajada / 1 - Por flanco de subida
	*EXTINT  |= (1<<2);				//Baja INTRP
}
