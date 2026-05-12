import random

# Snakes and ladders positions
board = {
    2: 38, 7: 14, 8: 31, 15: 26,
    16: 6, 21: 42, 28: 84, 36: 44,
    46: 25, 49: 11, 51: 67, 62: 19,
    64: 60, 71: 91, 74: 53, 78: 98,
    87: 94, 89: 68, 92: 88, 95: 75,
    99: 80
}

# Function to roll dice
def roll_dice():
    return random.randint(1, 6)

# Function to move player
def move_player(position, dice):
    position += dice

    # Prevent crossing 100
    if position > 100:
        return position - dice

    # Check snake or ladder
    if position in board:
        if position < board[position]:
            print("Ladder! Climb up")
        else:
            print("Snake! Go down")

        position = board[position]

    return position

# Initial positions
player1 = 0
player2 = 0

# Game loop
while True:

    input("Player 1 turn: Press Enter to roll dice ")
    dice = roll_dice()

    print("Dice:", dice)

    player1 = move_player(player1, dice)

    print("Player 1 position:", player1)

    # Check winner
    if player1 == 100:
        print("Player 1 Wins!")
        break

    input("Player 2 turn: Press Enter to roll dice ")
    dice = roll_dice()

    print("Dice:", dice)

    player2 = move_player(player2, dice)

    print("Player 2 position:", player2)

    # Check winner
    if player2 == 100:
        print("Player 2 Wins!")
        break