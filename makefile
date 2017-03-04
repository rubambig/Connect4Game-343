#*******************************************************
# Produces the executable from the .c files
# @author Gloire Rubambiza
# @version 02/28/2017
#********************************************************/#
Connect: connect_four.c
	clang connect_four.c handle_arguments.c file_utils.c -o Connect

# Creating different boards to test for rubustness
# Board1 Creates a square board
# Board2 Creates a board with higher height than width
# Board3 Creates a board with higher width than height
test: Board1 Board2 Board3

Board1:
	./Connect -w 4 -h 4 -c 3


Board2:
	./Connect -w 5 -h 8 -c 4

Board3:
	./Connect -w 9 -h 5 -c 4
