import matplotlib
from matplotlib import pyplot as plt
from random import randint
import copy

GEN_TAB = 1
PRINT_TAB = 2
CHANGE_W = 3
SHOW_RES = 4
EXIT = 0
def get_right_vect_elem(table, k):
    sum = 0
    for i in range(len(table[0])):
        xi = pow(table[0][i], (k))
        sum += (table[2][i] * xi * table[1][i])
    return sum
    
def get_left_vect(table, k, m):
    sum = 0
    for i in range(len(table[0])):
        xi = pow(table[0][i], (k + m))
        sum += (table[2][i] * xi)
    return sum
def gauss(matrix):
    matr = copy_matr(matrix)
    for i in range (len(matr[0]) - 1):
        for j in range(i + 1, len(matr[0])):
            if (i == j):
                continue
            k = matr[j][i] / matr[i][i] 
            for l in range (len(matr[0])):
                matr[j][l] -= (matr[i][l] * k)
    ans = 1    
    for i in range (len(matr[0])):
        ans *= matr[i][i]
    return float(ans)
                

def build_slau(table, power):
    slau_matr = []
    vect = []
    for i in range(power + 1):
        vect1 = []
        for j in range (power + 1):
            vect1.append(get_left_vect(table, i, j))
        slau_matr.append(vect1)
        vect.append(get_right_vect_elem(table, i))

    return slau_matr, vect
def print_matr(matr):
    for i in range (len(matr[0])):
        print(matr[i], "\n")
def copy_col(matr_copy, vect, i):
    for j in range (len(vect)):
        matr_copy[j][i] = vect[j]
    return matr_copy
def copy_matr(matr2):
    matr1 = []
    for i in  range(len(matr2)):
        vect = []
        for j in range (len(matr2[0])):
            vect.append(matr2[i][j])
        matr1.append(vect)
    return matr1
def solve_slau_kramer(slau_matr, vect):
    free_memb = copy.deepcopy(vect)
    
    det_arr = []
    
    ans_arr = []

    matr_copy = copy_matr(slau_matr)
    for i in range (len(vect)):
        matr_copy = copy_matr(slau_matr)
        
        matr_copy = copy_col(matr_copy, vect, i)
        
        ans_arr.append(gauss(matr_copy) / gauss(slau_matr))
    return ans_arr
        
def get_dots(table, power, eps=0.01):
        matrix, vect = build_slau(table, power)
        
        result = solve_slau_kramer(matrix, vect)

        x, y = [], []
        k = table[0][0] - eps
        while k <= table[0][len(table[0]) - 1] + eps:
            y_cur = 0
            for j in range(0, power + 1):
                y_cur += result[j] * pow(k, j)

            x.append(k)
            y.append(y_cur)

            k += eps
        
        return x, y

def set_default_weights(table):
        for i in range(len(table[0])):
            table[2][i] = 1

def draw(table, flag_changed):
        power = int(input("Введите степень полинома: "))

        if flag_changed:
            changed_table = copy.deepcopy(table)
            set_default_weights(table)

        for cur_power in range(1, power + 1):
            if cur_power > 2 and cur_power < power:
                continue

            x, y = get_dots(table, cur_power)
            plt.plot(x, y, label="Равный вес:\nn = %d" % (cur_power))

            if flag_changed:
                x, y = get_dots(changed_table, cur_power)

                plt.plot(x, y, label="Разные веса:\nn = %d" % (cur_power))

        x_arr = copy.deepcopy(table[0])
        y_arr = copy.deepcopy(table[1])

        plt.plot(x_arr, y_arr, "o", label="Date")
        plt.legend()
        plt.grid()
        plt.xlabel("X")
        plt.ylabel("Y")
        plt.show()

        if flag_changed:
           table = changed_table


def sort_table(table):
    for i in range(len(table[0])-1):
        for j in range(len(table[0]) - i - 1):
            if table[0][j] > table[0][j+1]:
                table[0][j], table[0][j+1] = table[0][j+1], table[0][j]
                table[1][j], table[1][j+1] = table[1][j+1], table[1][j]
                table[2][j], table[2][j+1] = table[2][j+1], table[2][j]

def generate_table(size):
    local_tab = [[], [], []]
    for i in range(size):
        local_tab[0].append(randint(1.0, 100.0)); local_tab[1].append(randint(1.0, 100.0)); local_tab[2].append(1.0);
    sort_table(local_tab)
    return local_tab
def print_table(table):
    print("|      №      |      X      |      F(X)      |      W      |")
    print("------------------------------------------------------------")
    for i in range (len(table[0])):
        print("|      %-6d |      %-6.1f |      %-6.1f    |      %-6.1f |\n" % (i + 1, table[0][i], table[1][i], table[2][i]))
        #print("------------------------------------------------------------")
def change_weight(table):
    ind = int(input("Введите номер узла для изменения веса:\n"))
    new_w = float(input("Введите новый вес:\n"))
    table[2][ind - 1] = new_w
table = [[], [], []]
choice = None
flag = 0
while (True):
    print(" 1 - Генерация таблицы\n 2 - Печать таблицы\n 3 - Изменить вес\n 4 - Вывод результатов\n 0 - Exit\n")
    choice = int(input("Выберите действие:"))
    if (choice == EXIT):
        break

    elif (choice == GEN_TAB):
        table = generate_table (8)
    elif (choice == PRINT_TAB):
        print_table(table)
    elif (choice == CHANGE_W):
        change_weight(table)
        flag = 1
    elif (choice == SHOW_RES):
        draw(table, flag)
