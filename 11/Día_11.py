# input, sample
PATH = 'input'

def mult(old, val):
    if val == 'old':
        return old * old
    else:
        return old * val

def add(old, val):
    return old + val

def load_monkey_data(input):
    monkeys = []
    current_monkey = {}
    for line in input:
        line = line.split()
        if len(line) < 2:
            continue
        elif line[0] == 'Monkey':
            monkeys.append({'count' : 0})
            current_monkey = monkeys[-1]
        elif line[0] == 'Starting':
            items = []
            for item in line[2:]:
                item = item.replace(',', '')
                items.append(int(item))
            current_monkey['items'] = items
        elif line[0] == 'Operation:':
            if line[4] == '*':
                current_monkey['op'] = mult
            elif line[4] == '+':
                current_monkey['op'] = add

            if line[5] == 'old':
                current_monkey['val'] = 'old'
            else:
                current_monkey['val'] = int(line[5])
        elif line[0] == 'Test:':
            current_monkey['mod'] = int(line[3])
        elif line[0:2] == ['If', 'true:']:
            current_monkey['t_dest'] = int(line[5])
        elif line[0:2] == ['If', 'false:']:
            current_monkey['f_dest'] = int(line[5])

    return monkeys

def calculate_monkey_business(input, rounds, div):
    monkeys = load_monkey_data(input)

    # mcm de todos los módulos
    mod = 1
    for monkey in monkeys:
        mod *= monkey['mod']

    for _ in range(rounds):
        for monkey in monkeys:
            while len(monkey['items']) > 0:
                monkey['count'] += 1
                item = monkey['items'].pop(0)
                item = int(monkey['op'](item, monkey['val']) / div)
                if item % monkey['mod'] == 0:
                    monkeys[monkey['t_dest']]['items'].append(item % mod)
                else:
                    monkeys[monkey['f_dest']]['items'].append(item % mod)

    inspections = []
    for monkey in monkeys:
        inspections.append(monkey['count'])
    inspections.sort()

    res = inspections[-2] * inspections[-1]

    return res

def part_one(input):
    return calculate_monkey_business(input, 20, 3)

def part_two(input):
    return calculate_monkey_business(input, 10000, 1)

input = (open(PATH).read().splitlines())
print('1 - La cantidad de negocio primate es', part_one(input))
print('2 - La cantidad de negocio primate sin dividir es', part_two(input))

# Negocio primate: 59272
# Negocio sin dividir: 14952185856