import serial
from queue import Queue

queue = Queue()


def send_error():
    pass


def send_ok():
    pass


def listen():
    ser = serial.Serial(
        port='/dev/ttyUSB1',
        baudrate=115200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        timeout=10,
        bytesize=serial.EIGHTBITS
    )

    ser.isOpen()

    translate = dict(
            pkgsize=3,
            arriba='w',
            abajo='s',
            izquierda='a',
            derecha='d',
            selec=' '
        )
    while True:
        intruccion = ser.read(translate['pkgsize'])
        if intruccion in translate.keys():
            queue.put(translate['instruccion'])
            send_ok()
        else:
            send_error()


if __name__ == "__main__":
    listen()

