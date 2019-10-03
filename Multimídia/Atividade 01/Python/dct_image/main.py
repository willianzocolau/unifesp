import utils as lib
import os

version, comments, numrows, numcols, profundidade, data = lib.readpgm(os.getcwd() + '/image.pgm')

matrix = lib.dividir_blocos(data, (8, 8))
matrix_zig = matrix.copy()

for x in range(matrix.shape[0]):
    for y in range(matrix.shape[1]):
        matrix[x][y], matrix_zig[x][y] = lib.dct_block_8(matrix[x][y], matrix_zig[x][y])

matrix = lib.juntar_blocos(matrix)
matrix_zig = matrix_zig.reshape(numrows, numcols)

lib.export_to_file(version, comments, numrows, numcols, profundidade, matrix)

zig = lib.zigzag2(matrix_zig.copy())
print("\nQuantidade de zero's disponível para descarte: " + str(zig))
