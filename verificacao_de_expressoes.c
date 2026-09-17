#include <stdio.h>
#include <string.h>
#include "pilhas.h"

static int corresponde(char abertura, char fechamento) {
    return (abertura == '(' && fechamento == ')') ||
           (abertura == '[' && fechamento == ']') ||
           (abertura == '{' && fechamento == '}');
}

static int ehAbertura(char c) {
    return (c == '(' || c == '[' || c == '{');
}

static int ehFechamento(char c) {
    return (c == ')' || c == ']' || c == '}');
}

int verificarExpressao(const char* exp) {
    if (exp == NULL) {
        return 0;
    }

    Pilha p;
    inicializar(&p);

    for (size_t i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];

        if (ehAbertura(c)) {
            push(&p, c);
        } else if (ehFechamento(c)) {
            if (isEmpty(&p)) {
                liberar(&p);
                return 0;
            }

            char topo = pop(&p);
            if (!corresponde(topo, c)) {
                liberar(&p);
                return 0;
            }
        }
    }

    int valido = isEmpty(&p);
    liberar(&p);
    return valido;
}

int main(void) {
    char expressao[100];

    printf("Digite a expressao: ");
    if (fgets(expressao, sizeof(expressao), stdin) == NULL) {
        return 1;
    }

    expressao[strcspn(expressao, "\n")] = '\0';

    if (verificarExpressao(expressao)) {
        printf("Expressao verdadeira!\n");
    } else {
        printf("Expressao falsa!\n");
    }

    return 0;
}
