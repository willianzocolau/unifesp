import numpy as np


class Data:
    i = 0
    j = 0
    count = 0
    size = 0
    n = 0
    sentido = 1
    troca = 1

    def get_position(self):
        if self.i < self.n and self.troca == 1:
            if self.sentido == 1 and self.i == 0:
                self.sentido = -1
                self.j += 1
            elif self.sentido == 1 and self.i > 0:
                self.i -= 1
                self.j += 1
            elif self.sentido == -1 and self.j == 0:
                self.sentido = 1
                self.i += 1
            elif self.sentido == -1 and self.j > 0:
                self.j -= 1
                self.i += 1
        else:
            self.troca = -1
            if self.sentido == -1 and self.i == self.n:
                self.sentido = 1
                self.j += 1
            elif self.sentido == -1 and self.i < self.n:
                self.i += 1
                self.j -= 1
            elif self.sentido == 1 and self.j == self.n:
                self.sentido = -1
                self.i += 1
            elif self.sentido == 1 and self.j < self.n:
                self.j += 1
                self.i -= 1


def zigzag(matrix, size):
    p = Data()
    p.size = size * size
    p.n = size - 1
    while p.count < p.size:
        print(str(matrix[p.i][p.j]) + ' na posição (' + str(p.i) + ', ' + str(p.j) + ')')
        p.get_position()
        p.count += 1


matrix = np.array([
    [80, 60, 50, 80, 120, 200, 255, 255],
    [55, 60, 70, 95, 130, 255, 255, 255],
    [70, 65, 80, 120, 200, 255, 255, 255],
    [70, 85, 110, 145, 255, 255, 255, 255],
    [90, 110, 185, 255, 255, 255, 255, 255],
    [120, 175, 255, 255, 255, 255, 255, 255],
    [245, 255, 255, 255, 255, 255, 255, 255],
    [255, 255, 255, 255, 255, 255, 255, 255]
])

matrix = np.random.rand(2056, 2056)
size = matrix.shape[0]
zigzag(matrix, size)
