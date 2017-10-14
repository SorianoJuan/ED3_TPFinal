import sys
from PyQt5 import QtCore, QtWidgets, QtSvg


class Gui(QtWidgets.QMainWindow):

    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        self.timer = QtCore.QTimer(self)
        self.svgW = QtSvg.QSvgWidget()
        self.initUI()

    def initUI(self):

        self.timer.timeout.connect(self.Refresh)
        self.timer.start(150)

        self.svgW.load('asd')

        self.setCentralWidget(self.svgW)

        #---------Window settings --------------------------------

        self.setGeometry(50, 50, 750, 750)
        self.setFixedSize(750, 750)
        self.setWindowTitle("Chess.ini")

    #-------- Slots ------------------------------------------

    def Refresh(self):
        self.svgW.load('asd')


def GUI():
    app = QtWidgets.QApplication(sys.argv)
    g = Gui()
    g.show()

    sys.exit(app.exec_())

if __name__ == "__main__":
    GUI()

