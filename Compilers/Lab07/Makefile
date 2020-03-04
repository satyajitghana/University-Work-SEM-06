all: ident

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: tokens.l parser.tab.h
	flex tokens.l

ident: main.c lex.yy.c parser.tab.c parser.tab.h
	gcc -o ident main.c parser.tab.c lex.yy.c

clean:
	rm ident parser.tab.c parser.tab.h lex.yy.c