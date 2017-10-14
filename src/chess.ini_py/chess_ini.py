import threading
import chess.svg
from chess_ini_GUI import GUI, modified, img_svg

t = threading.Thread(target=GUI)
t.start()

board = chess.Board()
img_svg.set_svg(chess.svg.board(board))
while True:
    act = input(">> ")
    if act == 'q':
        modified.set()
        break
    else:
        try:
            board.push(chess.Move.from_uci(act))
            img_svg.set_svg(chess.svg.board(board))
            modified.set()
        except ValueError:
            print("Nope")

