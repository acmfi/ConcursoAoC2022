# input, sample
PATH = 'input'

def move_head(direction, pos):
    x = pos[0]
    y = pos[1]
    if direction == 'R':
        x += 1
    elif direction == 'L':
        x -= 1
    elif direction == 'D':
        y += 1
    elif direction == 'U':
        y -= 1

    return (x, y)

def move_tail(head, tail):
    dx = head[0] - tail[0]
    dy = head[1] - tail[1]

    if abs(dx) + abs(dy) > 2:
        dx = max(-1, min(1, dx))
        dy = max(-1, min(1, dy))
    elif abs(dx) > 1:
        dx = max(-1, min(1, dx))
        dy = 0
    elif abs(dy) > 1:
        dx = 0
        dy = max(-1, min(1, dy))
    else:
        dx = 0
        dy = 0

    return (tail[0] + dx, tail[1] + dy)

def count_visited(input):
    visited = set()
    head = (0, 0)
    tail = (0, 0)
    for line in input:
        line = line.split(" ")
        for _ in range(int(line[1])):
            head = move_head(line[0], head)
            tail = move_tail(head, tail)
            visited.add(tail)
    return len(visited)

def count_for_len(input, rope_length):
    visited = set()
    head = (0, 0)
    body = [(0, 0)] * (rope_length - 2)
    tail = (0, 0)
    for line in input:
        line = line.split(" ")
        for _ in range(int(line[1])):
            head = move_head(line[0], head)
            previous_part = head
            for i in range(len(body)):
                body[i] = move_tail(previous_part, body[i])
                previous_part = body[i]
            tail = move_tail(previous_part, tail)
            visited.add(tail)
    return len(visited)

input = (open(PATH).read().splitlines())
print('1 - El número de casillas visitadas es', count_visited(input))
print('2 - Las casillas visitadas por la cuerda de longitud 10 es', count_for_len(input, 10))

# Casillas visitadas: 5779
# Casillas cuerda larga: 2331