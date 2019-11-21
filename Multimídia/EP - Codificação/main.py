import utils as lib
import os
import numpy as np

print('Iniciando...')
version, comments, numrows, numcols, profundidade, data = lib.readpgm(os.getcwd() + '/lena.pgm')

matrix = lib.dividir_blocos(data, (8, 8))
matrix_zig = matrix.copy()
matrix_zig1 = matrix.copy()
matrix_zig2 = matrix.copy()

for x in range(matrix.shape[0]):
    for y in range(matrix.shape[1]):
        matrix[x][y], matrix_zig[x][y] = lib.dct_block_8(matrix[x][y], matrix_zig[x][y], matrix.copy(), x, y)

for x in range(matrix.shape[0]):
    for y in range(matrix.shape[1]):
        matrix[x][y], matrix_zig1[x][y] = lib.dct_block_8(matrix[x][y], matrix_zig[x][y], matrix.copy(), x, y)

for x in range(matrix.shape[0]):
    for y in range(matrix.shape[1]):
        matrix[x][y], matrix_zig2[x][y] = lib.Idct_block_8(matrix[x][y], matrix_zig[x][y], matrix.copy(), x, y)

for x in range(matrix.shape[0]):
    for y in range(matrix.shape[1]):
        matrix[x][y], matrix_zig2[x][y] = lib.Idct_block_8(matrix[x][y], matrix_zig[x][y], matrix.copy(), x, y)

matrix_cod = matrix_zig.copy()
matrix = lib.juntar_blocos(matrix)
matrix_cod = lib.juntar_blocos(matrix_cod)

resultado = 0;
for x in range(matrix_zig.shape[0]):
    for y in range(matrix_zig.shape[1]):
         resultado += lib.zigzag2(matrix_zig[x][y].copy())

resultado3 = 0;
for x in range(matrix_zig1.shape[0]):
    for y in range(matrix_zig1.shape[1]):
         resultado3 += lib.zigzag2(matrix_zig1[x][y].copy())

resultado2 = lib.apply_codificacao(matrix_cod)

lib.export_to_file(version, comments, numrows, numcols, profundidade, matrix)

diferenca = resultado2 - resultado
necessario = (409600 - resultado2) * 2

print("Tradicional: " + str(resultado))
print("Outro Proposto: " + str(resultado3))
print("Proposto: " + str(resultado2))
print("Diferença: " + str(diferenca))
print("Necessario: " + str(necessario))
print("Compensa? " + str(necessario <= diferenca))

print('Finalizado!')