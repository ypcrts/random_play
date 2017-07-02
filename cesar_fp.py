
def normalize(c):
    if c not in 'QWERTYUIOPASDFGHJKLZXCVBNM':
        return c
    return ord(c) - ord('A')


def asciitransform(c):
    if not isinstance(c, int):
        return c
    return chr(ord('A') + c)


def enc(s):
    s = s.upper()
    s = list(map(normalize, s))
    s = list(map(lambda c: (c + 1 if isinstance(c, int) else c), s))
    return "".join(list(map(asciitransform, s)))


def dec(s):
    s = s.upper()
    s = list(map(normalize, s))
    s = list(map(lambda c: c - 1 if isinstance(c, int) else c, s))
    return "".join(list(map(asciitransform, s)))


if __name__ == '__main__':
    import sys
    if sys.argv[1] == 'e':
        print(enc(sys.argv[2]))
        exit(0)

    print(dec(sys.argv[2]))
