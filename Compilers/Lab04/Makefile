# name of the files and the program
NAME = lab04

# compiler setup
CC = g++
LEX = flex

all: ${NAME}

${NAME}: main.cpp lex.yy.c
	${CC} main.cpp lex.yy.c -o ${NAME}

lex.yy.c: ${NAME}.l
	${LEX} ${NAME}.l

clean:
	rm -f lex.yy.c  ${NAME}

run:
	@./${NAME}
