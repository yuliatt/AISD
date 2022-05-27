class Vertex(object):
    def __init__(self, data, pred):
        self.data = data
        self.son = pred + len(data)
        self.is_explored = False

    def __eq__(self, other):
        return self.son == other.son


def word_vertex(edge, path):
    counter = 0
    while True:
        try:
            vertex = path.index(edge, counter)
            yield vertex
            counter = vertex + 1
        except ValueError:
            break


def shortest_path(graph, count, ph_len):
    queue = [[vertex] for vertex in graph[count]]

    while queue:
        path = queue.pop(0)
        node = path[-1]
        if node.is_explored:
            continue
        try:
            nears = graph[node.son]
            for near in nears:
                new_path = list(path)
                new_path.append(near)
                queue.append(new_path)
                if near.son == ph_len:
                    return new_path
        except KeyError:
            pass

        node.is_explored = True

    return None


def word_to_number(num):
    alphabet = {'I': '1', 'J': '1',
                'A': '2', 'B': '2', 'C': '2',
                'D': '3', 'E': '3', 'F': '3',
                'G': '4', 'H': '4',
                'K': '5', 'L': '5',
                'M': '6', 'N': '6',
                'P': '7', 'R': '7', 'S': '7',
                'T': '8', 'U': '8', 'V': '8',
                'W': '9', 'X': '9', 'Y': '9',
                'O': '0', 'Q': '0', 'Z': '0',
                '0': '0', '1': '1', '2': '2', '3': '3', '4': '4', '5': '5', '6': '6', '7': '7',
                '8': '8', '9': '9'}
    return ''.join([alphabet[ch] for ch in num])


file = open('in.txt', 'r')
lines = file.readlines()
file.close()

phone = lines[0].strip()


is_begin = False
is_result = False
result = ''
dictionary = {}
n = int(lines[1].strip())
wordNumbers = [word_to_number(lines[i].strip()) for i in range(2, n + 2)]
lines.pop(0)
lines.pop(0)
for i in range(n):
    word = lines[i].strip()
    if is_result:
        continue
    number = wordNumbers[i]
    if number == phone:
        is_result = True
        result = word
    else:
        for position in word_vertex(number, phone):
            if position == 0:
                is_begin = True
            vertex_word = Vertex(word, position)
            try:
                if any(map(lambda w: w == vertex_word, dictionary[position])):
                    continue
                dictionary[position] += [vertex_word]
            except KeyError:
                dictionary[position] = [vertex_word]

file = open('out.txt', 'w')

if is_begin:
    result = shortest_path(dictionary, 0, len(phone))
    if result:
        file.write(str(len(result)) + '\n')
        file.write(' '.join([word.data for word in result]) + '\n')
    else:
        file.write('No solution')
else:
    file.write('No solution')
file.close()
