import chess.svg
board = chess.Board()
f = open('asd', 'w')
f.write(chess.svg.board(board=board))
f.close()
