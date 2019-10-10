import utils as lib
import os

print('Iniciando...')
version, comments, numrows, numcols, profundidade, data = lib.readpgm(os.getcwd() + '/exemplo.pgm')

matrix = lib.dividir_blocos(data, (8, 8))
matrix_zig = matrix.copy()

for x in range(matrix.shape[0]):
    for y in range(matrix.shape[1]):
        matrix[x][y], matrix_zig[x][y] = lib.dct_block_8(matrix[x][y], matrix_zig[x][y], matrix.copy(), x, y)

matrix = lib.juntar_blocos(matrix)

resultado = 0;
for x in range(matrix_zig.shape[0]):
    for y in range(matrix_zig.shape[1]):
         resultado += lib.zigzag2(matrix_zig[x][y].copy())

lib.export_to_file(version, comments, numrows, numcols, profundidade, matrix)

print(str(resultado))
print('Finalizado!')