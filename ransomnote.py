def ransom_note(magazine, ransom):
    """ransom_note

    The ransom note is cut out of the words of a magazine. Returns True iff the
    magazine is sufficient for the ransom note.

    :param magazine: The words of the magazine
    :param ransom: The words of a ransom note
    """
    mag_map = {}
    for w in magazine:
        mag_map[w] = mag_map.get(w, 0) + 1

    for w in ransom:
        count = mag_map.get(w)
        if not count:
            return False
        elif count > 1:
            mag_map[w] -= 1
        else:
            del mag_map[w]

    return True


m, n = map(int, input().strip().split(' '))
magazine = input().strip().split(' ')
ransom = input().strip().split(' ')
answer = ransom_note(magazine, ransom)
if(answer):
    print("Yes")
else:
    print("No")
    
