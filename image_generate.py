from PIL import Image, ImageFont, ImageDraw
import numpy

SIZE = H, W = 1000, 400
BLACK = 0, 0, 0
WHITE = 255, 255, 255
RED = 255, 0, 0
GREEN = 0, 255, 0
BLUE = 0, 0, 255


font = ImageFont.truetype("./font/OpenSans-ExtraBold.ttf", 100)
# ascent, descent = font.getmetrics()

if __name__ == '__main__':
    bim = Image.open('./gfx/bunny.ico')
    bim.thumbnail((100, 100))

    matrix = numpy.zeros((H, W, 3), numpy.int8)

    # background
    matrix[:, :] = WHITE

    # border
    matrix[:, 0] = RED
    matrix[:, W-1] = RED
    matrix[0, :] = RED
    matrix[H-1, :] = RED

    # vertical grid
    for i in range(0, W, 100):
        if i != 0:
            matrix[:, i] = BLUE

    # horizontol grid
    for i in range(0, H, 100):
        if i != 0:
            matrix[i, :] = BLUE

    im = Image.fromarray(matrix, 'RGB')

    draw = ImageDraw.Draw(im)

    # draw 0
    draw.text((72, H-120), '0', font=font, fill=BLUE)

    # draw 1-9
    h = 20
    w = H-220
    for i in range(9):
        draw.text((h, w), str(i+1), font=font, fill=BLUE)
        h += 100
        if (i+1) % 3 == 0:
            w -= 100
            h = 20

    # draw enter
    draw.text((W-80, H-172), '¬', font=font, fill=BLUE)

    # draw decimal
    draw.text((234, H-120), '.', font=font, fill=BLUE)

    # draw plus
    draw.text((W-80, H-372), '+', font=font, fill=BLUE)

    # draw /
    draw.text((W-268, 480), '/', font=font, fill=BLUE)

    # draw *
    draw.text((W-175, 490), '*', font=font, fill=BLUE)

    # draw -
    draw.text((W-68, 472), '-', font=font, fill=BLUE)

    small_font = ImageFont.truetype("./font/OpenSans-ExtraBold.ttf", 72)

    # draw stacks
    for i in range(5):
        draw.text((10, i*100), f'S{str(i)}', font=small_font, fill=BLUE)

    im.paste(bim, box=(0, 500))

    im.save('./gfx/generate.png')

    # to do add bg colors
