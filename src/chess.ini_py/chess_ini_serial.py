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

    rapidos = ['e', 'g', 'c', 'a']
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

            if instruccion in rapidos:
                queue.put(translate[instruccion])

            queue.put(translate[instruccion])

        else:
            print("[!]Error en lectura ", instruccion)
            send_error()


if __name__ == "__main__":
    listen()

