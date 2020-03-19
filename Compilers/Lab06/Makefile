# name of the files and the program
NAME = lab06

# compiler setup
CC = g++ -g
LEX = flex
YACC = bison -d

all: ${NAME}

${NAME}.tab.c ${NAME}.tab.h: ${NAME}.y
	${YACC} ${NAME}.y

lex.yy.c: ${NAME}.l ${NAME}.tab.h
	${LEX} ${NAME}.l

${NAME}: main.cpp lex.yy.c ${NAME}.tab.c ${NAME}.tab.h
	${CC} -o ${NAME} main.cpp lex.yy.c ${NAME}.tab.c ${NAME}.tab.h

clean:
	rm -f lex.yy.c lex.yy.o ${NAME} ${NAME}.tab.c ${NAME}.tab.h
	rm -f ${NAME}.tab.o
