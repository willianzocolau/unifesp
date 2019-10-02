import utils as lib
import os

version, comments, numrows, numcols, profundidade, data = lib.readpgm(os.getcwd() + '/teste_16.pgm')

matrix = lib.dividir_blocos(data, (8, 8))

for x in range(matrix.shape[0]):
    for y in range(matrix.shape[1]):
        matrix[x][y] = lib.dct_block_8(matrix[x][y])

matrix = lib.juntar_blocos(matrix)

lib.export_to_file(version, comments, numrows, numcols, profundidade, matrix)
