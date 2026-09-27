CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = main.o cadastro.o rede_amizade.o postagem.o historico.o sugeridos.o backup.o icone.o
EXEC = Confessions

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

icone.o: icone.rc
	windres icone.rc -o icone.o

clean:
	rm -f *.o $(EXEC)