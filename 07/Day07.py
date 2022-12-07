PATH = 'input'

def get_files(text):
    files = {}
    dir_tree = [files]
    current_dir = files
    for line in text:
        line = line.split(" ")
        if (line[0] == '$'):
            if (line[1] == 'cd'):
                if (line[2] == '/'):
                    dir_tree = [files]
                elif (line[2] == '..'):
                    dir_tree.pop()
                else:
                    dir_tree.append(current_dir[line[2]])

                current_dir = dir_tree[-1]
        else:
            if (line[0] == 'dir'):
                current_dir.update({line[1]: {}})
            else:
                current_dir.update({line[1]: int(line[0])})
    return files

def flatten_dirs(dirs):
    flat_dirs = [dirs]
    for dir in dirs.values():
        if type(dir) == dict:
            flat_dirs += flatten_dirs(dir)
    return flat_dirs

def get_dir_size(dir):
    size = 0
    for value in dir.values():
        if type(value) != int:
            size += get_dir_size(value)
        else:
            size += value
    return size

def sum_dirs_smaller_than(files, size):
    sum = 0
    files = flatten_dirs(files)
    for dir in files:
        a = get_dir_size(dir)
        if a <= size:
            sum += a
    return sum

def find_smallest_dir_for_size(files, required_size, total_size):
    needed_space = required_size - total_size + get_dir_size(files)
    files = flatten_dirs(files)
    selected_space = total_size
    for dir in files:
        a = get_dir_size(dir)
        if needed_space <= a < selected_space:
            selected_space = a
    return selected_space

def part_one(s):
    return sum_dirs_smaller_than(s, 100000)

def part_two(s):
    return find_smallest_dir_for_size(s, 30000000, 70000000)
   

s = get_files(open(PATH).read().splitlines())
print('1 - La suma del tamaño de directorios es ', part_one(s))
print('2 - El tamaño liberado es ', part_two(s))


# Suma tamaños: 1667443
# Tamaño borrado: 8998590