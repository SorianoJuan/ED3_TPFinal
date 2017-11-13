import serial
from queue import Queue

queue = Queue()

ser = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    # timeout=10,
    bytesize=serial.EIGHTBITS
)


def send_error():
    ser.write('e'.encode())


def send_finish():
    ser.write('f'.encode())


def send_c():
    ser.write('c'.encode())


def listen():

    aux = 0
    i = 0
    lentos = ['f', 'h', 'd', 'b']

    ser.isOpen()

    translate = dict(
            pkgsize=1,
            e='w',		# rapido arriba
            f='w',		# lento arriba
            g='s',		# rapido abajo
            h='s',		# lento abajo
            c='a',		# rapido izq
            d='a',		# lento izq
            a='d',		# rapido der
            b='d',		# lento der
            z=' ',		# seleccionar
            p='p'       # paso de turno
        )
    while True:
        instruccion = ser.read(translate['pkgsize'])
        instruccion = instruccion.decode()
        if instruccion in translate.keys():
            print(">> ", instruccion)

            if instruccion is not aux:
                queue.put(translate[instruccion])
                (aux, i) = (instruccion, 2) if instruccion in lentos else (0,0)
            else:
                aux = 0 if i is 0 else aux
                i -= 1

        else:
            print("[!]Error en lectura ", instruccion)
            send_error()


if __name__ == "__main__":
    listen()

