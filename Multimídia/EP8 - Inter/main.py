import utils as lib
import os

print('Iniciando...')
version1, comments1, numrows1, numcols1, profundidade1, data1 = lib.readpgm(os.getcwd() + '/teste_16.pgm')

# version2, comments2, numrows2, numcols2, profundidade2, data2 = lib.readpgm(os.getcwd() + '/lena1.pgm')

matrix = lib.dividir_blocos(data1, (8, 8))
matrix_zig = matrix.copy()

for x in range(matrix.shape[0]):
    for y in range(matrix.shape[1]):
        matrix[x][y], matrix_zig[x][y] = lib.dct_block_8(matrix[x][y], matrix_zig[x][y], matrix.copy(), x, y)

matrix = lib.juntar_blocos(matrix)

resultado = 0;
for x in range(matrix_zig.shape[0]):
    for y in range(matrix_zig.shape[1]):
         resultado += lib.zigzag2(matrix_zig[x][y].copy())



lib.export_to_file(version1, comments1, numrows1, numcols1, profundidade1, matrix)

print(str(resultado))
print('Finalizado!')