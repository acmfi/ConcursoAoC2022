from functools import cmp_to_key
import json

# input, sample
PATH = 'input'

CONTINUE = 0
RIGHT_ORDER = -1
WRONG_ORDER = 1

def read_input_in_pairs(input):
    list = []
    first = None
    second = None
    for line in input:
        if line == '':
            continue
        if first == None:
            first = json.loads(line)
        else:
            second = json.loads(line)
            list.append((first, second))
            first = None
            second = None
    return list

def read_input_in_list(input):
    list = []
    for line in input:
        if line == '':
            continue
        list.append(json.loads(line))
    return list

def check_int(a, b):
    if a < b:
        return RIGHT_ORDER
    elif a > b:
        return WRONG_ORDER
    else:
        return CONTINUE

def check_list(first_list, second_list):
    for i in range(1000000):
        if len(first_list) == len(second_list) == i:
            return CONTINUE
        if len(first_list) == i:
            return RIGHT_ORDER
        if len(second_list) == i:
            return WRONG_ORDER

        first = first_list[i]
        second = second_list[i]
        
        if type(first) == int and type(second) == int:
            result = check_int(first, second)
            if result != CONTINUE:
                return result
        elif type(first) == list and type(second) == list:
            result = check_list(first, second)
            if result != CONTINUE:
                return result
        else:
            if type(first) == int:
                first = [first]
            elif type(second) == int:
                second = [second]
            result = check_list(first, second)
            if result != CONTINUE:
                return result
            
    raise ValueError('No se pudo determinar el orden')

def cmp(a, b):
    return check_list(a, b)

def part_one(input):
    list = read_input_in_pairs(input)
    right_order = []
    for i in range(len(list)):
        result = check_list(list[i][0], list[i][1])
        if result == RIGHT_ORDER:
            right_order.append(i + 1)

    return sum(right_order)

def part_two(input):
    list = read_input_in_list(input)
    list.append([[2]])
    list.append([[6]])
    list.sort(key=cmp_to_key(cmp))
    first_index = list.index([[2]])
    second_index = list.index([[6]], first_index)
    return (first_index + 1) * (second_index + 1)

input = (open(PATH).read().splitlines())
print('La suma de los índices en orden correcto es', part_one(input))
print('La clave de decodificación es', part_two(input))

# Paquetes ordenados: 5532
# Clave decodificación: 20304