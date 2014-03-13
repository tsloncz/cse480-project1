import random

a = open('a.txt', 'w')
b = open('b.txt', 'w')

na = 1000
nb = 1000
for i in range(0, 500):
    a.write(str(na) + '\n')
    b.write(str(nb) + '\n')
    na += random.randint(0, 5)
    nb += random.randint(0, 5)
