import sys
from PyQt5 import QtCore, QtWidgets, QtSvg
import threading


class svgBoard:
    def __init__(self):
        self.svg = '0'

    def set_svg(self, svg):
        self.svg = svg

    def get_svg(self):
        return self.svg


class Gui(QtWidgets.QMainWindow):

    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        self.timer = QtCore.QTimer(self)
        self.svgW = QtSvg.QSvgWidget()
        self.initUI()

    def initUI(self):

        self.timer.timeout.connect(self.Refresh)
        self.timer.start(0)

        self.svgW.load(img_svg.get_svg().encode())

        self.setCentralWidget(self.svgW)

        #---------Window settings --------------------------------

        size = QtWidgets.QDesktopWidget().screenGeometry()
        size = min(size.height(), size.width()) - 20
        self.setGeometry(50, 50, size, size)
        self.setFixedSize(size, size)
        self.setWindowTitle("Chess.ini")

    #-------- Slots ------------------------------------------

    def Refresh(self):
        if modified.is_set():
            self.svgW.load(img_svg.get_svg().encode())
            modified.clear()

        if finished.is_set():
            QtWidgets.QMessageBox.information(self, "RIP", "Ganaste wachin")
            exit()


def GUI():
    app = QtWidgets.QApplication(sys.argv)
    g = Gui()
    g.show()

    sys.exit(app.exec_())

modified = threading.Event()
finished = threading.Event()
img_svg = svgBoard()

if __name__ == "__main__":
    GUI()

