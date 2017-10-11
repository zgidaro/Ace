# Ace


# Moves

# Tokens can move to an adjacent destination if it is empty and within the board.
# Tokens on a black cell can move HORIZONTALLY, VERTICALLY, and DIAGONALLY.
# Tokens on a white cell can move HORIZONTALLY, and VERTICALLY

# Turns

# Green ALWAYS plays FIRST

# Attacks

# Forward Attack: Move token 1 cell TOWARDS an opponent's token and land next to a sequence of n consecutive tokens.
# The n tokens can be removed from the board.

# Backward Attack: Move token 1 cell AWAY from a an opponent's sequence of n consecutive tokens.
# The n tokens can be removed from the board.

# Defensive Move: Move token to adjacent cell without attacking an opponent's token.

### An attack that can be a forward or backward attack is ALWAYS a FORWARD attack. ###

# End Game

# Attack all of opponent's tokens and remove them from play.
# After 5 consecutive non-attacking moves from each player (10 consecutive non-attacking total) the game is a draw.