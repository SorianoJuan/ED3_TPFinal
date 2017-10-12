# import chess
import chess.svg
from tempfile import NamedTemporaryFile
from PyQt5 import QtWidgets, QtSvg
import sys

board = chess.Board("8/8/8/8/4N3/8/8/8 w - - 0 1")
squares = board.attacks(chess.E4)
img = chess.svg.board(board=board, squares=squares)

f = NamedTemporaryFile()

f.write(img.encode())

if __name__ == '__main__':

    app = QtWidgets.QApplication(sys.argv)

    svgWidget = QtSvg.QSvgWidget(f.name)
    # svgWidget.setGeometry(50, 50, 759, 668)
    svgWidget.setWindowTitle('Chessy')
    svgWidget.showMaximized()

    sys.exit(app.exec_())
