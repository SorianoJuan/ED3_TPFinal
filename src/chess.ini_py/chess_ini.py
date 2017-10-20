import threading
import chess.svg
from chess_ini_GUI import GUI, modified, img_svg

t = threading.Thread(target=GUI)
t.start()

board = chess.Board()
squares = [
    [chess.BB_A1, chess.BB_B1, chess.BB_C1, chess.BB_D1, chess.BB_E1, chess.BB_F1, chess.BB_G1, chess.BB_H1],
    [chess.BB_A2, chess.BB_B2, chess.BB_C2, chess.BB_D2, chess.BB_E2, chess.BB_F2, chess.BB_G2, chess.BB_H2],
    [chess.BB_A3, chess.BB_B3, chess.BB_C3, chess.BB_D3, chess.BB_E3, chess.BB_F3, chess.BB_G3, chess.BB_H3],
    [chess.BB_A4, chess.BB_B4, chess.BB_C4, chess.BB_D4, chess.BB_E4, chess.BB_F4, chess.BB_G4, chess.BB_H4],
    [chess.BB_A5, chess.BB_B5, chess.BB_C5, chess.BB_D5, chess.BB_E5, chess.BB_F5, chess.BB_G5, chess.BB_H5],
    [chess.BB_A6, chess.BB_B6, chess.BB_C6, chess.BB_D6, chess.BB_E6, chess.BB_F6, chess.BB_G6, chess.BB_H6],
    [chess.BB_A7, chess.BB_B7, chess.BB_C7, chess.BB_D7, chess.BB_E7, chess.BB_F7, chess.BB_G7, chess.BB_H7],
    [chess.BB_A8, chess.BB_B8, chess.BB_C8, chess.BB_D8, chess.BB_E8, chess.BB_F8, chess.BB_G8, chess.BB_H8],
]
par = (0, 0)
img_svg.set_svg(chess.svg.board(board=board, squares=chess.SquareSet(squares[par[1]][par[0]])))
legal = board.legal_moves
while True:
    act = input(">> ")
    if act == 'q':
        modified.set()
        break
    elif act == 'a':
        par = (par[0] - 1, par[1]) if par[0] > 0 else (0, par[1])
    elif act == 'd':
        par = (par[0] + 1, par[1]) if par[0] < 8 else (8, par[1])
    elif act == 'w':
        par = (par[0], par[1] + 1) if par[1] < 8 else (par[0], 8)
    elif act == 's':
        par = (par[0], par[1] - 1) if par[1] > 0 else (par[0], 0)
    else:
        act = chess.Move.from_uci(act)
        try:
            if act in legal:
                board.push(act)
            else:
                raise ValueError
        except ValueError:
            print("Nope")

    img_svg.set_svg(chess.svg.board(board=board, squares=chess.SquareSet(squares[par[1]][par[0]])))
    modified.set()
