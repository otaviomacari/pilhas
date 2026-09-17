#include <stdio.h>
#include <stdlib.h>
#include "pilhas.h"

// inicializando a pilha vazia
void inicializar(Pilha* p) {
    p->topo = NULL;
}

// verificando se a pilha esta vazia
int isEmpty(Pilha* p) {
    return (p->topo == NULL);
}

// empilhando um elemento no topo
void push(Pilha* p, char valor) {
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de alocacao!\n");
        return;
    }

    novo->dado = valor;
    novo->prox = p->topo;
    p->topo = novo;
}

// removendo o elemento do topo e retornando seu valor
char pop(Pilha* p) {
    if (isEmpty(p)) {
        return '\0';
    }

    No* temp = p->topo;
    char valor = temp->dado;

    p->topo = temp->prox;
    free(temp);

    return valor;
}

// retornando o valor do topo sem remover
char peek(Pilha* p) {
    if (isEmpty(p)) {
        return '\0';
    }

    return p->topo->dado;
}

// liberando todos os elementos da pilha
void liberar(Pilha* p) {
    while (!isEmpty(p)) {
        pop(p);
    }
}
