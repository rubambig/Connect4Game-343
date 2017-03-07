#******************************************
# Produces the executable from the .c files
# @author Gloire Rubambiza
# @version 02/28/2017
#******************************************/#
Connect: main.c
	clang main.c connect_four.c handle_arguments.c file_utils.c -o Connect


# Creating different boards to test for rubustness
# Board1 Creates a square board
# Board2 Creates a board with higher height than width
# Board3 Creates a board with higher width than height
test: Board1 Board2 Board3 Board4 Board5 Board6

# Plays a small prototype game for checking win conditions
Board1:
	./Connect -w 4 -h 4 -c 3

# Plays a game that is longer than wider
Board2:
	./Connect -w 5 -h 10 -c 4

# Plays a game that is wider than it is longer
Board3:
	./Connect -w 9 -h 5 -c 4

# Tests that the win condition is not greater than dimensions
Board4:
	./Connect -w 4 -h 3 -c 5

# Tests that the specification of a square is taken care of.
Board5:
	./Connect -w 6 -h 7 -c 3 -s 5

# Tests user input that is less than 0
Board6:
	./Connect -w -3 -h 6 -c -1
