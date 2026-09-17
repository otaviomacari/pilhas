#ifndef PILHAS_H
#define PILHAS_H

// definindo a struct do no da pilha
typedef struct No {
    char dado;
    struct No* prox;
} No;

// definindo a struct da pilha
typedef struct {
    No* topo;
} Pilha;

// funcoes da pilha
void inicializar(Pilha* p);
void push(Pilha* p, char valor);
char pop(Pilha* p);
char peek(Pilha* p);
int isEmpty(Pilha* p);
void liberar(Pilha* p);

#endif
