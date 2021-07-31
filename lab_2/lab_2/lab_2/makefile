CC = gcc
INCP = ./inc/
SRCP = ./src/
.PHONY: clean
app.exe: main.o funcs.o
	$(CC) -o app.exe main.o funcs.o
main.o:	$(SRCP)main.c $(INCP)funcs.h
	$(CC) -c -o main.o $(SRCP)main.c
funcs.o: $(SRCP)funcs.c $(INCP)funcs.h
	$(CC) -c -o funcs.o $(SRCP)funcs.c
clean:
	rm -fv *.o
	rm -fv *.exe

