def normalize(s):
    return list(map(_normalize_alpha_ord, s.upper()))


def _normalize_alpha_ord(c):
    if c not in 'QWERTYUIOPASDFGHJKLZXCVBNM':
        return c
    return ord(c) - ord('A')


def ascii_transform(s):
    return list(map(_ascii_transofrm_alpha_ord, s))


def _ascii_transofrm_alpha_ord(c):
    if not isinstance(c, int):
        return c
    return chr(ord('A') + c)


def vignere_transform(k, s, factor=1):
    plain_chars_count = 0
    for i, c in enumerate(s):
        if not isinstance(c, int):
            plain_chars_count += 1
            continue
        s[i] += k[i % len(k)] * factor
        s[i] %= 26
    return s


def enc(k, s):
    s = normalize(s)
    k = normalize(k)
    vignere_transform(k, s)
    return "".join(ascii_transform(s))


def dec(k, s):
    s = normalize(s)
    k = normalize(k)
    vignere_transform(k, s, -1)
    return "".join(ascii_transform(s))


if __name__ == '__main__':
    import sys
    if sys.argv[1] == 'e':
        print(enc(sys.argv[2], sys.argv[3]))
        exit(0)

    print(dec(sys.argv[2], sys.argv[3]))
