#include "direcciones.h"
#include "uart.h"

void uart_config (void){
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
}
