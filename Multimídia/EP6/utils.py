import numpy as np
import warnings
from random import randrange

warnings.filterwarnings("ignore")

# ORIGINAL = np.array([
#         [154, 123, 123, 123, 123, 123, 123, 136],
#         [192, 180, 136, 154, 154, 154, 136, 110],
#         [254, 198, 154, 154, 180, 154, 123, 123],
#         [239, 180, 136, 180, 180, 166, 123, 123],
#         [180, 154, 136, 167, 166, 149, 136, 136],
#         [128, 136, 123, 136, 154, 180, 198, 154],
#         [123, 105, 110, 149, 136, 136, 180, 166],
#         [110, 136, 123, 123, 123, 136, 154, 136]
#     ])

# lib.dct_block_8(ORIGINAL)
from numpy.lib.stride_tricks import as_strided


def dividir_blocos(matrix, block=(3, 3)):
    shape = (int(matrix.shape[0] / block[0]), int(matrix.shape[1] / block[1])) + block
    strides = (matrix.strides[0] * block[0], matrix.strides[1] * block[1]) + matrix.strides
    return as_strided(matrix, shape=shape, strides=strides)


def juntar_blocos(blocks):
    return np.hstack(np.vstack(map(np.hstack, blocks)))


def readpgm(name):
    with open(name) as f:
        lines = f.readlines()

    version = lines[0]
    comments = lines[1]
    numrows = int(lines[2].split(" ")[0], 10)
    numcols = int(lines[2].split(" ")[1], 10)
    profundidade = int(lines[3], 10);

    for x in range(4):
        lines.remove(lines[0])

    data = []
    for i in range(numrows):
        row = []
        for j in range(numcols):
            row.append(int(lines[0], 10))
            lines.remove(lines[0])
        data.append(row)

    return (version, comments, numrows, numcols, profundidade, np.array(data))


def normalized(value):
    if value < 0:
        return 0
    elif value > 255:
        return 255
    else:
        return value


def limite_inf(value):
    if (value) < 0:
        return 0
    else:
        return value


def limite_sup(value):
    if (value + 1) > 7:
        return 7
    else:
        return value + 1


def intra_prediction_down(original, matrix, x, y, value):
    for i in range(8):
        for j in range(8):
            if x - 1 < 0: continue
            original[j][i] = original[j][i] + (value * matrix[x-1][y][7][i])

def intra_prediction_right(original, matrix, x, y, value):
    for i in range(8):
        for j in range(8):
            if y - 1 < 0: continue
            original[j][i] = original[j][i] + (value * matrix[x][y-1][i][7])


def intra_prediction_above(original, matrix, x, y, value):
    for i in range(8):
        for j in range(8):
            if x + 1 > 79: continue
            original[j][i] = original[j][i] + (value * matrix[x + 1][y][0][i])


def dct_block_8(ORIGINAL, zig, matrix, x, y):
    Q_90 = [
        [3, 2, 2, 3, 5, 8, 10, 12],
        [2, 2, 3, 4, 5, 12, 12, 11],
        [3, 3, 3, 5, 8, 11, 14, 11],
        [3, 3, 4, 6, 10, 17, 16, 12],
        [4, 4, 7, 11, 14, 22, 21, 15],
        [5, 7, 11, 13, 16, 12, 23, 18],
        [10, 13, 16, 17, 21, 24, 24, 21],
        [14, 18, 19, 20, 22, 20, 20, 20]
    ]

    Q_50 = [
        [16, 11, 10, 16, 24, 40, 51, 61],
        [12, 12, 14, 19, 26, 58, 60, 55],
        [14, 13, 16, 24, 40, 57, 69, 56],
        [14, 17, 22, 29, 51, 87, 80, 62],
        [18, 22, 37, 56, 68, 109, 103, 77],
        [24, 35, 55, 64, 81, 104, 113, 92],
        [49, 64, 78, 87, 103, 121, 120, 101],
        [72, 92, 95, 98, 112, 100, 103, 99]
    ]

    Q_10 = [
        [80, 60, 50, 80, 120, 200, 255, 255],
        [55, 60, 70, 95, 130, 255, 255, 255],
        [70, 65, 80, 120, 200, 255, 255, 255],
        [70, 85, 110, 145, 255, 255, 255, 255],
        [90, 110, 185, 255, 255, 255, 255, 255],
        [120, 175, 255, 255, 255, 255, 255, 255],
        [245, 255, 255, 255, 255, 255, 255, 255],
        [255, 255, 255, 255, 255, 255, 255, 255]
    ]

    intra_prediction_above(ORIGINAL, matrix, x, y, -1)

    M = ORIGINAL - 128

    T = np.array([
        [0.3536, 0.3536, 0.3536, 0.3536, 0.3536, 0.3536, 0.3536, 0.3536],
        [0.4904, 0.4157, 0.2778, 0.0975, -0.0975, -0.2778, -0.4157, -0.4904],
        [0.4619, 0.1913, -0.1913, -0.4619, -0.4619, -0.1913, 0.1913, 0.4619],
        [0.4157, -0.0975, -0.4904, -0.2778, 0.2778, 0.4904, 0.0975, -0.4157],
        [0.3536, -0.3536, -0.3536, 0.3536, 0.3536, -0.3536, -0.3536, 0.3536],
        [0.2778, -0.4904, 0.0975, 0.4157, -0.4157, -0.0975, 0.4904, -0.2778],
        [0.1913, -0.4619, 0.4619, -0.1913, -0.1913, 0.4619, -0.4619, 0.1913],
        [0.0975, -0.2778, 0.4157, -0.4904, 0.4904, -0.4157, 0.2778, -0.0975]
    ])

    D = np.dot(T, M)
    D = np.dot(D, T.transpose())
    D = D.round(1)

    C = np.divide(D, Q_50)
    C = C.round()

    R = Q_50 * C

    zig = R.copy()

    N = np.dot(T.transpose(), R)
    N = np.dot(N, T)
    N = N.round()

    intra_prediction_above(N, matrix, x, y, 1)

    for i in range(8):
        for j in range(8):
            N[i][j] = normalized(N[i][j] + 128)

    return N, zig


def export_to_file(version, comments, numrows, numcols, profundidade, matrix):
    f = open("image_dct.pgm", "w+")

    f.write(version)
    f.write(comments)
    f.write(str(numrows) + " " + str(numcols) + "\n")
    f.write(str(profundidade) + "\n")

    for i in range(numrows * numcols):
        f.write(str(matrix[i]) + "\n")

    f.close()


def zigzag(rows, columns, matrix):
    solution = [[] for i in range(rows + columns - 1)]

    for i in range(rows):
        for j in range(columns):
            sum = i + j
            if (sum % 2 == 0):
                solution[sum].insert(0, matrix[i][j])
            else:
                solution[sum].append(matrix[i][j])

    result = 0
    for i in range(solution.__len__() - 1, 0, -1):
        non_zeros = np.count_nonzero(solution[i])
        zeros = solution[i].__len__() - non_zeros
        if non_zeros > 0:
            break
        result += zeros
    return result


def zigzag2(input):
    h = 0
    v = 0
    vmin = 0
    hmin = 0
    vmax = input.shape[0]
    hmax = input.shape[1]
    i = 0
    output = np.zeros((vmax * hmax))
    while ((v < vmax) and (h < hmax)):
        if ((h + v) % 2) == 0:
            if (v == vmin):
                output[i] = input[v, h]
                if (h == hmax):
                    v = v + 1
                else:
                    h = h + 1
                i = i + 1
            elif ((h == hmax - 1) and (v < vmax)):
                output[i] = input[v, h]
                v = v + 1
                i = i + 1
            elif ((v > vmin) and (h < hmax - 1)):
                output[i] = input[v, h]
                v = v - 1
                h = h + 1
                i = i + 1
        else:
            if ((v == vmax - 1) and (h <= hmax - 1)):
                output[i] = input[v, h]
                h = h + 1
                i = i + 1
            elif (h == hmin):
                output[i] = input[v, h]
                if (v == vmax - 1):
                    h = h + 1

                else:
                    v = v + 1
                i = i + 1

            elif ((v < vmax - 1) and (h > hmin)):
                output[i] = input[v, h]
                v = v + 1
                h = h - 1
                i = i + 1

        if ((v == vmax - 1) and (h == hmax - 1)):
            output[i] = input[v, h]
            break

    result = 0
    for i in range(output.__len__() - 1, 0, -1):
        if output[i] != 0:
            break
        result += 1

    return result
