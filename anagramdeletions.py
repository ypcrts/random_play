from __future__ import print_function
import sys


def deletions(a, b):
    """deletions

    Output the number of deletions required
    to make a and b anagrams of each other 

    :param a:
    :param b:
    """
    ds = 0
    a_map = {}
    b_map = {}

    for c in a:
        a_map[c] = a_map.get(c, 0) + 1

    for c in b:
        b_map[c] = b_map.get(c, 0) + 1

    for c, n in a_map.items():
        if c not in b_map:
            ds += n
        elif a_map[c] != b_map[c]:
            ds += abs(a_map[c] - b_map[c])

    for c, n in b_map.items():
        if c not in a_map:
            ds += n

    print(ds)


if __name__ == '__main__':
    deletions(sys.stdin.readline().strip(), sys.stdin.readline().strip())
