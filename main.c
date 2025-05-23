#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match(char t, char palavra[], int *pos);
void trataErro(int pos, char esperado, char encontrado);
char dentroDoVetor(char c, char vetor[], int tamanho);
int E(char palavra[], int *pos);
int X(char palavra[], int *pos);
int K(char palavra[], int *pos);
int T(char palavra[], int *pos);
int F(char palavra[], int *pos);
int Z(char palavra[], int *pos);
int D(char palavra[], int *pos);
int N(char palavra[], int *pos);

char lookahead;

int match(char t, char palavra[], int *pos) {
    if (lookahead == t) {
        lookahead = palavra[++(*pos)];
        return 1;
    } else {
        trataErro(*pos, t, lookahead);
        return 0;
    }
}

void trataErro(int pos, char esperado, char encontrado) {
    printf("\nErro de sintaxe na posição %d: esperado '%c', encontrado '%c'\n", pos, esperado, encontrado);
    exit(1);
}

char dentroDoVetor(char c, char vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (c == vetor[i]) {
            return c;
        }
    }
    return 'X';
}

// E → X
int E(char palavra[], int *pos) {
    if (X(palavra, pos)) return 1;
    else return 0;
}

// X → T K
int X(char palavra[], int *pos) {
    if (T(palavra, pos) && K(palavra, pos)) return 1;
    else return 0;
}

// K → + T K | - T K | ε
int K(char palavra[], int *pos) {
    if (lookahead == '+') {
        match('+', palavra, pos);
        if (T(palavra, pos) && K(palavra, pos)) return 1;
        else return 0;
    } else if (lookahead == '-') {
        match('-', palavra, pos);
        if (T(palavra, pos) && K(palavra, pos)) return 1;
        else return 0;
    }
    return 1;
}

// T → F Z
int T(char palavra[], int *pos) {
    if (F(palavra, pos) && Z(palavra, pos)) return 1;
    else return 0;
}

// Z → * F Z | / F Z | ε
int Z(char palavra[], int *pos) {
    if (lookahead == '*') {
        match('*', palavra, pos);
        if (F(palavra, pos) && Z(palavra, pos)) return 1;
        else return 0;
    } else if (lookahead == '/') {
        match('/', palavra, pos);
        if (F(palavra, pos) && Z(palavra, pos)) return 1;
        else return 0;
    }
    return 1;
}

// F → (X) | -N | N
int F(char palavra[], int *pos) {
    if (lookahead == '(') {
        match('(', palavra, pos);
        if (X(palavra, pos) && match(')', palavra, pos)) {
            return 1;
        } else {
            return 0;
        }
    } else if (lookahead == '-') {
        match('-', palavra, pos);
        if (N(palavra, pos)) return 1;
        else return 0;
    } else if (N(palavra, pos)) {
        return 1;
    } else {
        return 0;
    }
}

// N → [0-9] D
int N(char palavra[], int *pos) {
    char v[10] = {'0','1','2','3','4','5','6','7','8','9'};
    char num = dentroDoVetor(lookahead, v, 10);
    if (num != 'X') {
        match(num, palavra, pos);
        if (D(palavra, pos)) return 1;
        else return 0;
    }
    return 0;
}

// D → [0-9] D | ε
int D(char palavra[], int *pos) {
    char v[10] = {'0','1','2','3','4','5','6','7','8','9'};
    char num = dentroDoVetor(lookahead, v, 10);
    if (num != 'X') {
        match(num, palavra, pos);
        return D(palavra, pos);
    }
    return 1;
}

int main() {
    FILE *arquivo = fopen("entrada.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo entrada.txt\n");
        return 1;
    }

    char palavra[256];
    fscanf(arquivo, "%s", palavra);
    fclose(arquivo);

    int pos = 0;
    lookahead = palavra[pos];

    printf("Expressão a ser analisada: %s\n", palavra);

    if (E(palavra, &pos) && palavra[pos] == '\0') {
        printf("Expressão válida!\n");
    } else {
        printf("Expressão inválida!\n");
    }

    return 0;
}
