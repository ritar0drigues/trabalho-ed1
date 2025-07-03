all: run

programa: main.c atividade.c evento.c fila.c participante.c pilha.c utils.c
	gcc -o programa main.c atividade.c evento.c fila.c participante.c pilha.c utils.c

run: programa
	./programa

clean:
	rm -f programa