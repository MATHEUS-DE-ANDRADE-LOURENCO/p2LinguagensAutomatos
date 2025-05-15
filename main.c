# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int match(char t, char palavra[], int *pos);
void trataErro();
char dentroDoVetor(char c, char vetor[], int tamanho);
int E(char palavra[], int *pos);
int X(char palavra[], int *pos);
int K(char palavra[], int *pos);
int T(char palavra[], int *pos);
int F(char palavra[], int *pos);
int Z(char palavra[], int *pos);
int D(char palavra[], int *pos);
int N(char palavra[], int *pos);

char lookahead; // Próximo caractere da palavra

int  match(char t, char palavra[], int *pos){
	if (lookahead == t){ // Se o próximo caractere for igual a t
		lookahead= palavra[++(*pos)]; // Avança mais um caractere na palavra
		return(1); // Verdadeiro
	}
	return(0);  // Falso
}

void trataErro(){
	printf("\n\nERRO DE SINTAXE\n\n");
	/* IMPORTANTE:  Faca um tratamento melhor !!! */
}

char dentroDoVetor(char c, char vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (c == vetor[i]) {
            return c;
        }
    }
    return 'X';
}

int E(char palavra[], int *pos){
    if (X(palavra, pos) && match('$', palavra, pos)) return 1;
    else return 0;
}

int X(char palavra[], int *pos){
   if(T(palavra, pos) && K(palavra, pos)) return 1;
   else return 0;
}

int K(char palavra[], int *pos){
    if(lookahead == '+') {
        match('+', palavra, pos);
       if(T(palavra, pos) && K(palavra, pos)) return 1;
        else return 0; 
    } else if (lookahead == '-') {
        match('-', palavra, pos);
       if(T(palavra, pos) && K(palavra, pos)) return 1;
        else return 0; 
    }else return 1; // Caso para palavra vazia
}

int T(char palavra[], int *pos){   
   if(F(palavra, pos) && Z(palavra, pos)) return 1;
   else return 0;
}

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
        if (N(palavra, pos)) {
            return 1;
        } else {
            return 0;
        }
    } else if (N(palavra, pos)) {
        return 1;
    } else {
        return 0;
    }
}

int Z(char palavra[], int *pos){
    if(lookahead == '/') {
        match('/', palavra, pos);
       if(F(palavra, pos) && Z(palavra, pos)) return 1;
        else return 0; 
    } else if (lookahead == '*') {
        match('*', palavra, pos);
       if(F(palavra, pos) && Z(palavra, pos)) return 1;
        else return 0; 
    }else return 1; // Caso para palavra vazia
}

int D(char palavra[], int *pos){
    char v[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    char num = dentroDoVetor(lookahead, v, 10);

    if(num != 'X') {
        match(num, palavra, pos);
        if(D(palavra, pos)) return 1;
        else return 0;
    } else return 1;
}

int N(char palavra[], int *pos){
    char v[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    char num = dentroDoVetor(lookahead, v, 10);

    if(num != 'X') {
        match(num, palavra, pos);
        if(D(palavra, pos)) return 1;
        else return 0;
    } else return 0;
}

int main() {
    char palavra[] = "98$";
    int pos = 0;

    lookahead = palavra[pos];
    if (E(palavra, &pos))
	    printf("\nPalavra %s reconhecida\n\n", palavra);
	else 
	    printf("\nPalavra %s não reconhecida\n\n", palavra);
	system("PAUSE");
	return(0);

}