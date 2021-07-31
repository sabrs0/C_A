
import numpy as np
from numpy.polynomial.legendre import *
from numpy.linalg import eigvalsh
from math import cos, sin, exp, pi


def funcarr(deg):
    c = np.array([0]*deg + [1])
    m = legcompanion(c)
    x = eigvalsh(m)
    dy = legval(x, c)
    df = legval(x, legder(c))
    x -= dy/df
    fm = legval(x, c[1:])
    fm /= np.abs(fm).max()
    df /= np.abs(df).max()
    w = 1/(fm * df)
    w = (w + w[::-1])/2
    x = (x - x[::-1])/2
    w *= 2. / w.sum()
    return x, w


def Gauss(curFunction, end, start, num):
    legArr = funcarr(num)
    output = 0
    for i in range(num):
        output += (start - end) / 2 * legArr[1][i] * curFunction((end + start) / 2 + (end - start) * legArr[0][i] / 2)
    return output


def Simpson(curFunction, start, end, num):
    h = (end - start) / (num - 1)
    x = start
    output = 0
    for i in range((num - 1) // 2):
        output += curFunction(x) + 4 * curFunction(x + h) + curFunction(x + 2 * h)
        x += 2 * h
    output *= h / 3
    return output

def onetemp(twoParSolvation, imput):
    return lambda x: twoParSolvation(imput, x)


def bothparam(curFunction, limits, num, integrators):
    interior = lambda x: integrators[1](onetemp(curFunction, x), limits[1][0], limits[1][1], num[1])
    return integrators[0](interior, limits[0][0], limits[0][1], num[0])


def resolver(tao):
    subcurFunction = lambda x, y: 2 * cos(x) / (1 - (sin(x) * sin(x)) * (cos(y) * cos(y)))
    curFunction = lambda x, y: (4 / pi) * (1 - exp(-tao * subcurFunction(x, y))) * cos(x) * sin(x)
    return curFunction

tao = int(input("tao: "))
N = int(input("n: "))
M = int(input("m: "))
output = bothparam(resolver(tao), ((0, pi / 2), (0, pi / 2)), (N, M), (Gauss, Simpson))
print(output)
