def get_value(s):
    if s.isdigit():
        return int(s)
    return 10

def winner(player, dealer):
    if player > 21:
        return False
    if dealer > 21:
        return True
    if dealer > player:
        return False
    return True

def deal(player, dealer, count, stopped, c, acc):
    if count < 4:
        if count % 2 == 0:
            if c[0] == 'A':
                deal(player+1, dealer, count+1, stopped, c[1:], acc)
                deal(player+11, dealer, count+1, stopped, c[1:], acc)
            else:
                deal(player+get_value(c[0]), dealer, count+1, stopped, c[1:], acc)
        else:
            if c[0] == 'A':
                if dealer + 11 < 22:
                    deal(player, dealer+11, count+1, stopped, c[1:], acc)
                else:
                    deal(player, dealer+1, count+1, stopped, c[1:], acc)
            else:
                deal(player, get_value(c[0])+dealer, count+1, stopped, c[1:], acc)
    elif stopped:
        if dealer > 16:
            acc.append(winner(player, dealer))
        else:
            if len(c) == 0:
                return acc.append(winner(player, dealer))
            if c[0] == 'A':
                if dealer + 11 < 22:
                    deal(player, dealer+11, count+1, stopped, c[1:], acc)
                else:
                    deal(player, dealer+1, count+1, stopped, c[1:], acc)
            else:
                deal(player, get_value(c[0])+dealer, count+1, stopped, c[1:], acc)
    else:
        if player > 21:
            acc.append(False)
        else:
            if len(c) == 0:
                return acc.append(winner(player, dealer))
            deal(player, dealer, count, True, c, acc)
            if c[0] == 'A':
                deal(player+1, dealer, count+1, stopped, c[1:], acc)
                deal(player+11, dealer, count+1, stopped, c[1:], acc)
            else:
                deal(player+get_value(c[0]), dealer, count+1, stopped, c[1:], acc)

inp = input()

while inp != "JOKER":
    acc = []
    deal(0, 0, 0, False, inp, acc)
    if True in acc:
        print('Yes')
    else:
        print('No')
    inp = input()



