import threading
import chess.svg
from chess_ini_GUI import GUI, modified, img_svg, finished
from chess_ini_serial import *


def wait_input():
    return queue.get()

t = list()
t.append(threading.Thread(target=GUI))
t.append(threading.Thread(target=listen))
t[0].start()
t[1].start()

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
par_white = [0, 0]
par_black = [7, 7]
par = par_black
square = None
mov = list()
last_action = 0
img_svg.set_svg(chess.svg.board(board=board, squares=chess.SquareSet(squares[par[1]][par[0]])))
legal = board.legal_moves
while True:

    if board.is_game_over():
        print("GAMEEEE OVERRRRR BITCH!")
        send_finish()
        finished.set()
        break

    act = wait_input()
    if act == 'q':
        modified.set()
        break

    if last_action is 0:
        if act == 'p':
            par = par_black if par is par_white else par_white
            last_action = 1
        else:
            send_error()
            continue
    else:
        if act == 'a':
            par[0] = par[0] - 1 if par[0] > 0 else 0
        elif act == 'd':
            par[0] = par[0] + 1 if par[0] < 7 else 7
        elif act == 'w':
            par[1] = par[1] + 1 if par[1] < 7 else 7
        elif act == 's':
            par[1] = par[1] - 1 if par[1] > 0 else 0
        elif act == ' ':
            square = list(chess.SquareSet(squares[par[1]][par[0]]))[0]
            mov.append(square)
            try:
                if len(mov) == 2:
                    square = None
                    mov = chess.Move(mov[0], mov[1])
                    if mov in legal:

                        if board.is_capture(mov):
                            send_c()

                        board.push(mov)
                        mov = list()
                        last_action = 0
                    else:
                        raise ValueError
                else:
                    if board.piece_at(square) is None:
                        square = None
                        raise ValueError
            except ValueError:
                    mov = list()
                    print("Nope")
                    send_error()

    img_svg.set_svg(chess.svg.board(board=board, squares=chess.SquareSet(squares[par[1]][par[0]]), check=square))
    modified.set()
