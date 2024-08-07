import random
print(5)
for i in range(5):
    L = random.randint(1, 5)
    R = random.randint(1, 5)
    if L > R:
        L, R = R, L
    print(L, R)
for i in range(5):
    print(random.randint(-10, 10), end=" ")
