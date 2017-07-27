if __name__ == "__main__":
    H,W = map(int, input().split())
    board = []
    for x in range(H):
        board.append(input())
    print ('#' * (W + 2))
    for y in range(H):
        print ('#' + board[y] + '#')
    print ('#' * (W + 2))
