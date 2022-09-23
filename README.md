# Wordle-Solver
This solver will work in two different ways -- either the secret word may be known to the user and specified to the program (useful for testing purposes, so that the program can whittle down the search space until it finds the specified word), or the solver can iteratively suggest guesses to the user, so as to search for solutions to a live problem.

Each color in the response gives us information, constraining the remaining
search space. Here we guessed "irate", and the official Wordle game gave us
back: gray, green, gray, yellow, green. We represent this in our programs as
"xgxyg".