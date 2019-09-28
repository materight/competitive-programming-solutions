import math

T = int(input())

for t in range(0, T):
    N, L = [int(s) for s in input().split()]

    msg = [None]*(L+1)
    # Leggo i dati
    products = [int(s) for s in input().split()]
    s = 0
    # Trovo i prim elementi diversi
    while products[s] == products[s+1]:
        s += 1
    msg[s+1] = math.gcd(products[s], products[s+1])
    msg[s] = products[s] // msg[s+1]
    for i in range(s + 2, L + 1):
        msg[i] = products[i - 1] // msg[i - 1]
        i += 1
    for i in range(s - 1, -1, -1):
        msg[i] = products[i + 1] // msg[i + 1]
        i += 1
    sorted_msg = msg.copy()
    sorted_msg.sort()
    alphabet = {}
    alphabet[sorted_msg[0]] = 'A'
    for i in range(1, L + 1):
        if sorted_msg[i] != sorted_msg[i - 1]:
            alphabet[sorted_msg[i]] = chr(ord(alphabet[sorted_msg[i - 1]]) + 1)

    text = ''.join(list(map(lambda x: alphabet[x], msg)))
    print("Case #{}: {}".format(t+1, text))
