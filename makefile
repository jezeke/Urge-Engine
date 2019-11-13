EXEC=urge
CC=gcc
CFLAGS=-Wall -g
OBJ=list.o logging.o render.o simulation.o

urge: init.c $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lpthread -lm -L /usr/X11R6/lib -lX11 init.c -o $(EXEC)

list.o: list.c
	$(CC) $(CFLAGS) -c list.c

logging.o: logging.c
	$(CC) $(CFLAGS) -c logging.c

render.o: render.c
	$(CC) $(CFLAGS) -c render.c

simulation.o: simulation.c
	$(CC) $(CFLAGS) -c simulation.c

clean:
	rm $(OBJ) $(EXEC)
