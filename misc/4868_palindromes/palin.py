


def is_palindrome(s):
    l = len(s)
    if l % 2 == 1:
        s = s[:l//2] + s[l//2+1:]
    expected_right = s[:l//2][::-1]
    return expected_right == s[l//2:]

inp = input()
while inp != "0":

    n = int(inp)
    ct = 0
    while not is_palindrome(str(n+ct).zfill(len(inp))):
        ct += 1
    print(ct)
    inp = input()

