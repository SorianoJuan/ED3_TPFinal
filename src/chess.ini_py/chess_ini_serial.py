import serial
from chess_ini import queue

def send_error():
    pass


def send_ok():
    pass


def listen():
    ser = serial.Serial()

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
