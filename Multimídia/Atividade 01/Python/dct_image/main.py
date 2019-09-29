import utils as lib
import os

version, comments, numrows, numcols, profundidade, data = lib.readpgm(os.getcwd() + '/image.pgm')

A = lib.dividir_blocos(data, (8, 8))

for x in range(A.shape[0]):
    for y in range(A.shape[1]):
        A[x][y] = lib.dct_block_8(A[x][y])

A = lib.juntar_blocos(A)

f = open("image_dct.pgm", "w+")

f.write(version)
f.write(comments)
f.write(str(numrows) + " " + str(numcols) + "\n")
f.write(str(profundidade) + "\n")

for i in range(numrows*numcols):
    f.write(str(A[i]) + "\n")

f.close()