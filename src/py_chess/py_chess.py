import chess.svg
from wand.image import Image
from wand.color import Color
from wand import display

board = chess.Board()

img_svg = chess.svg.board(board=board)

with Image(blob=img_svg.encode(), format='svg', resolution=175) as img:
    img.background_color = Color('white')
    img.alpha_channel = 'remove'
    display.display(img)

