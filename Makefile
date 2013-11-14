CC = gcc
CFLAGS = -c -g
LD = gcc
LDFLAGS = -o
TARGET = minicc
$(TARGET): main.o hash.o token.o parser.o type.o env.o global.o lexer.o id.o
	$(LD) main.o hash.o token.o parser.o type.o env.o global.o lexer.o id.o $(LDFLAGS) $@

hash.o: hash.c
	$(CC) $(CFLAGS) $<

token.o: token.c
	$(CC) $(CFLAGS) $<

parser.o: parser.c
	$(CC) $(CFLAGS) $<

type.o: type.c
	$(CC) $(CFLAGS) $<

env.o: env.c
	$(CC) $(CFLAGS) $<

global.o: global.c
	$(CC) $(CFLAGS) $<

lexer.o: lexer.c
	$(CC) $(CFLAGS) $<

id.o: id.c
	$(CC) $(CFLAGS) $<

main.o: main.c
	$(CC) $(CFLAGS) $<


test: test.c token.c
	$(CC) hash.c test.c token.c type.c global.c lexer.c -g -o test
.PHONY: clean
clean:
	rm *.o minicc
