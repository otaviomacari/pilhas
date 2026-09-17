# Verificação de Expressões com Pilha em C

Projeto desenvolvido em **linguagem C** para verificar se uma expressão possui seus **parênteses, colchetes e chaves corretamente balanceados**.

O projeto utiliza uma estrutura de dados do tipo **Pilha (Stack)** implementada manualmente com **lista encadeada**, permitindo exercitar conceitos de estruturas de dados, ponteiros, alocação dinâmica de memória e gerenciamento de nós.

---

## Objetivo

O programa recebe uma expressão digitada pelo usuário e verifica se todos os símbolos de abertura possuem seus respectivos símbolos de fechamento na ordem correta.

São considerados:

* `(` → `)`
* `[` → `]`
* `{` → `}`

Por exemplo:

```text
{[()]}
```

é uma expressão válida.

Já:

```text
{[(])}
```

é inválida, pois os símbolos não estão na ordem correta.

---

## Como funciona

A verificação utiliza o conceito de **Pilha (LIFO — Last In, First Out)**.

Durante a leitura da expressão:

1. Quando um símbolo de abertura é encontrado, ele é colocado na pilha através da função `push()`.
2. Quando um símbolo de fechamento é encontrado, o elemento que está no topo da pilha é removido através da função `pop()`.
3. O símbolo removido é comparado com o símbolo de fechamento utilizando a função `corresponde()`.
4. Caso os símbolos não correspondam, a expressão é considerada inválida.
5. Ao final da leitura, a pilha precisa estar vazia para que a expressão seja considerada válida.

### Exemplo

Para a expressão:

```text
{[()]}
```

A pilha funciona da seguinte maneira:

```text
Lê '{' → PUSH

TOP
 ↓
 {

Lê '[' → PUSH

TOP
 ↓
 [
 ↓
 {

Lê '(' → PUSH

TOP
 ↓
 (
 ↓
 [
 ↓
 {

Lê ')' → POP
'(' corresponde a ')'

Lê ']' → POP
'[' corresponde a ']'

Lê '}' → POP
'{' corresponde a '}'

Pilha vazia → Expressão válida
```

---

# Estrutura do Projeto

O projeto está dividido em três arquivos principais:

```text
.
├── pilhas.c
├── pilhas.h
└── verificacao_de_expressoes.c
```

---

## `pilhas.h`

O arquivo `pilhas.h` funciona como o **arquivo de cabeçalho da pilha**.

Nele são declaradas as estruturas utilizadas e os protótipos das funções.

### Estrutura do nó

```c
typedef struct No {
    char dado;
    struct No* prox;
} No;
```

Cada elemento da pilha é representado por um nó contendo:

* `dado` → armazena o caractere;
* `prox` → aponta para o próximo nó da pilha.

### Estrutura da pilha

```c
typedef struct {
    No* topo;
} Pilha;
```

A estrutura `Pilha` possui apenas um ponteiro chamado `topo`, responsável por indicar o elemento que está no topo da pilha.

---

# `pilhas.c`

O arquivo `pilhas.c` contém a implementação das funções da pilha.

## `inicializar()`

```c
void inicializar(Pilha* p) {
    p->topo = NULL;
}
```

Inicializa a pilha deixando o ponteiro `topo` como `NULL`.

Isso representa uma pilha vazia.

---

## `isEmpty()`

```c
int isEmpty(Pilha* p) {
    return (p->topo == NULL);
}
```

Verifica se a pilha está vazia.

Retorna:

* `1` → pilha vazia;
* `0` → pilha possui elementos.

---

## `push()`

```c
void push(Pilha* p, char valor)
```

Adiciona um novo elemento ao topo da pilha.

Para isso, é utilizado `malloc()` para realizar a **alocação dinâmica de memória**.

O novo nó recebe o valor e passa a apontar para o antigo topo:

```c
novo->dado = valor;
novo->prox = p->topo;
p->topo = novo;
```

Assim, o novo elemento passa a ser o topo da pilha.

---

## `pop()`

```c
char pop(Pilha* p)
```

Remove o elemento que está no topo da pilha e retorna seu valor.

O nó removido é liberado utilizando:

```c
free(temp);
```

Isso evita o acúmulo de memória não utilizada.

---

## `peek()`

```c
char peek(Pilha* p)
```

Retorna o valor que está no topo da pilha **sem removê-lo**.

Embora essa função não seja utilizada diretamente na verificação da expressão, ela faz parte da implementação da estrutura de dados.

---

## `liberar()`

```c
void liberar(Pilha* p)
```

Remove todos os elementos da pilha.

A função utiliza `pop()` repetidamente até que a pilha fique vazia:

```c
while (!isEmpty(p)) {
    pop(p);
}
```

Essa função garante que a memória alocada dinamicamente seja liberada corretamente.

---

# `verificacao_de_expressoes.c`

Esse é o arquivo responsável pela aplicação da pilha na verificação das expressões.

## `corresponde()`

```c
static int corresponde(char abertura, char fechamento)
```

Verifica se um símbolo de abertura corresponde ao seu respectivo símbolo de fechamento.

As combinações válidas são:

```text
( )
[ ]
{ }
```

A função retorna `1` quando existe correspondência e `0` caso contrário.

---

## `ehAbertura()`

```c
static int ehAbertura(char c)
```

Verifica se determinado caractere é um símbolo de abertura:

```text
(
[
{
```

---

## `ehFechamento()`

```c
static int ehFechamento(char c)
```

Verifica se determinado caractere é um símbolo de fechamento:

```text
)
]
}
```

---

# `verificarExpressao()`

A função:

```c
int verificarExpressao(const char* exp)
```

é responsável pela lógica principal do projeto.

Primeiro, uma pilha é criada e inicializada:

```c
Pilha p;
inicializar(&p);
```

Depois, o programa percorre cada caractere da expressão:

```c
for (size_t i = 0; exp[i] != '\0'; i++)
```

### Quando encontra uma abertura

O caractere é colocado na pilha:

```c
if (ehAbertura(c)) {
    push(&p, c);
}
```

### Quando encontra um fechamento

Primeiro é verificado se existe algum elemento na pilha.

Caso ela esteja vazia, significa que apareceu um fechamento sem uma abertura correspondente:

```c
if (isEmpty(&p)) {
    liberar(&p);
    return 0;
}
```

Caso exista um elemento, ele é retirado:

```c
char topo = pop(&p);
```

Depois é verificado se o símbolo retirado corresponde ao fechamento atual:

```c
if (!corresponde(topo, c)) {
    liberar(&p);
    return 0;
}
```

Se não corresponder, a expressão é considerada inválida.

---

## Verificação final

Depois que todos os caracteres foram analisados:

```c
int valido = isEmpty(&p);
```

A pilha precisa estar vazia.

Isso significa que todas as aberturas encontradas tiveram seus respectivos fechamentos.

Por fim:

```c
liberar(&p);
return valido;
```

A memória utilizada pela pilha é liberada e o resultado da verificação é retornado.

---

# Exemplos

### Expressão válida

Entrada:

```text
Digite a expressao: {[()]}
```

Saída:

```text
Expressao verdadeira!
```

### Expressão inválida

Entrada:

```text
Digite a expressao: {[(])}
```

Saída:

```text
Expressao falsa!
```

### Outro exemplo válido

```text
(a + b) * [c - d]
```

Saída:

```text
Expressao verdadeira!
```

### Outro exemplo inválido

```text
([)]
```

Saída:

```text
Expressao falsa!
```

---

# Caracteres ignorados

O programa verifica somente:

```text
( ) [ ] { }
```

Outros caracteres, como letras, números, operadores e espaços, são ignorados durante a verificação.

Por exemplo:

```text
a + (b * [c + d])
```

é analisada considerando apenas:

```text
([ ])
```

---

# Complexidade

Considerando uma expressão com `n` caracteres:

### Tempo

A expressão é percorrida uma única vez.

**Complexidade:**

```text
O(n)
```

### Espaço

No pior caso, todos os caracteres analisados podem ser símbolos de abertura e armazenados na pilha.

**Complexidade:**

```text
O(n)
```

---

# Conceitos praticados

Este projeto permite praticar diversos conceitos fundamentais de **Estruturas de Dados em C**:

* Pilhas;
* Lista encadeada;
* Estrutura `struct`;
* Ponteiros;
* Ponteiros para estruturas;
* Alocação dinâmica de memória;
* `malloc()`;
* `free()`;
* Lógica LIFO;
* Manipulação de caracteres;
* Modularização através de `.c` e `.h`;
* Funções;
* Verificação de expressões;
* Gerenciamento de memória.

---

# Compilação

Utilizando o GCC, os três arquivos podem ser compilados juntos:

```bash
gcc pilhas.c verificacao_de_expressoes.c -o verificacao
```

Depois, execute:

### Windows

```bash
verificacao.exe
```

### Linux/macOS

```bash
./verificacao
```

---

# Fluxo do programa

```text
                Expressão
                    │
                    ▼
          Percorre cada caractere
                    │
          ┌─────────┴─────────┐
          │                   │
      Abertura             Fechamento
          │                   │
          ▼                   ▼
       PUSH              Pilha vazia?
                              │
                       ┌──────┴──────┐
                       │             │
                      Sim           Não
                       │             │
                       ▼             ▼
                    Inválida        POP
                                     │
                                     ▼
                              Correspondem?
                                     │
                              ┌──────┴──────┐
                              │             │
                             Não           Sim
                              │             │
                              ▼             ▼
                           Inválida     Continua
                                             │
                                             ▼
                                  Final da expressão
                                             │
                                             ▼
                                      Pilha vazia?
                                             │
                                      ┌──────┴──────┐
                                      │             │
                                     Sim           Não
                                      │             │
                                      ▼             ▼
                                   Válida        Inválida
```

---

## Conclusão

O projeto demonstra uma aplicação prática da estrutura de dados **Pilha**, utilizando o princípio **LIFO (Last In, First Out)** para solucionar o problema de balanceamento de delimitadores em expressões.

A implementação da pilha foi feita utilizando **lista encadeada e alocação dinâmica**, permitindo que os elementos sejam adicionados e removidos conforme necessário, sem a necessidade de definir previamente um tamanho fixo para a estrutura.

