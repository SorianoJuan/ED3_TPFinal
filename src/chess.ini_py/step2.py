import chess.svg
board = chess.Board()
board.push_san("e4")
f = open('asd', 'w')
f.write(chess.svg.board(board=board))
f.close()
