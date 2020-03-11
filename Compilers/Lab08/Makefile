all: calc

calc.tab.c calc.tab.h: calc.y
	bison -d calc.y

lex.yy.c: calc.l calc.tab.h
	flex calc.l

calc: main.c lex.yy.c calc.tab.c calc.tab.h
	gcc -w -o calc main.c calc.tab.c lex.yy.c

clean:
	rm calc calc.tab.c calc.tab.h lex.yy.c