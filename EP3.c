/***************************************************************/
/**                                                           **/
/**   Caio de Souza Barbosa Costa        Número USP: 11257734 **/
/**   Exercício-Programa 03                                   **/
/**   Professor: Alair                                        **/
/**   Turma: 01                                               **/
/**                                                           **/
/***************************************************************/

/*
OBSERVAÇÃO: Para evitar o warning "warning: ignoring return value of ‘scanf’, declared with attribute warn_unused_result [-Wunused-result]"
ao usar "gcc -Wall -ansi -pedantic -O2 EP2.c -o EP2" (compilador pedido pelas intruções do EP), foi feito

    if(scanf("%d", &entrada) != 1) {
        printf("ERRO: Não foi possível ler a entrada! \n");
        return 0;
    } 

que tem o mesmo efeito de scanf("%d", &entrada);
*/

#include <stdio.h>
#include <stdlib.h>

#define MMAX 90
#define NMAX 90

/* Definicao de constantes de direcao */
#define CENTRO 0
#define NORTE 1
#define NORDESTE 2
#define LESTE 3
#define SUDESTE 4
#define SUL 5
#define SUDOESTE 6
#define OESTE 7
#define NOROESTE 8


/*
    @brief Responsavel pelo loop de entrada
*/

void entrada(int *m, int *n, int *z, int *seed) {
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    do {
        printf("Numero de linhas (3 <= m <= 90): ");
        if (scanf("%d", &a) != 1) {
            a = 0; /* forca um erro */
        }
    } while (a < 3 || a > MMAX);

    do {
        printf("Numero de colunas (3 <= n <= 90): ");
        if (scanf("%d", &b) != 1) {
            b = 0;
        }
    } while (b < 3 || b > NMAX);

    do {
        printf("Numero de minas (1 <= z <= %d): ", (a * b - 1));
        if (scanf("%d", &c) != 1) {
            c = 0;     
        }   
    } while (c < 1 || c > (a * b - 1));

    do {
        printf("Semente (1 <= s <= 12345): ");
        if (scanf("%d", &d) != 1) {
            d = 0; 
        }       
    } while (d < 1 || d > 12345);

    *m = a;
    *n = b;
    *z = c;
    *seed = d;
}

void novo_seed(int *seed) {
    srand(*seed);
    *seed = rand() % 12345 + 1;
}

int posicao_linha_aleatoria(int linhas, int *seed) {
    int numero = 0;

    srand(*seed);
    numero = rand();
    return numero % linhas + 1;
}

int posicao_coluna_aleatoria(int linhas, int colunas, int *seed) {
    int numero = 0;

    srand(*seed);
    numero = rand();
    return (numero / linhas) % colunas + 1;
}

/* A funcao abaixo nao sera usada provavelmente */

int numero_de_adjacentes(int N, int NE, int E, int SE, int S, int SW, int W, int NW) {
    int adjacentes = 0;

    if (N == 1)
        adjacentes++;
    if (NE == 1)
        adjacentes++;
    if (E == 1) 
        adjacentes++;
    if (SE == 1)
        adjacentes++;
    if (S == 1)
        adjacentes++;
    if (SW == 1)
        adjacentes++;
    if (W == 1)
        adjacentes++;
    if (NW == 1)
        adjacentes++;

    return adjacentes;  
}



int main() {
    int m = 0; /*numero de linhas*/
    int n = 0; /*numero de colunas*/
    int z = 0; /*numero de minas*/
    int seed = 0;
    int tabuleiro[90][90][9];

    int morto = 0;
    int N_casas_abertas = 0;
    int casas_abertas[90][90];
    int N_casas_mercadas = 0;
    int casas_marcadas[90][90];

    /* Variaveis de Loop */
    int zero1 = 0;
    int zero2 = 0;
    int zero3 = 0;

    int count = 0;
    int count2 = 0;
    int count3 = 0;
    /*********************/

    entrada(&m, &n, &z, &seed);
    printf("%d %d %d %d \n", m, n, z, seed);

    /* Zera todo o vetor tabuleiro, casas_abertas e casas_marcadas */
    for (zero1 = 0; zero1 < m; zero1++) {
        for (zero2 = 0; zero2 < n; zero2++) {
            for (zero3 = 0; zero3 < 9; zero3++) {
                tabuleiro[zero1][zero2][zero3] = 0;
            }
            casas_abertas[zero1][zero2] = 0;
            casas_marcadas[zero1][zero2] = 0;
        }
    }

    /* Gera o tabuleiro e suas solucoes */
    while (count <= z) {
        int posicao_linha = posicao_linha_aleatoria(m, &seed);
        int posicao_coluna = posicao_coluna_aleatoria(m, n, &seed);
        novo_seed(&seed);
        tabuleiro[posicao_linha][posicao_coluna][0] = 1;
        count++;
    }

    printf("\n");
    for (count2 = 0; count2 < m; count2++) {
        for (count3 = 0; count3 < n; count3++) {
            printf("%d ", tabuleiro[count2][count3][0]);
            if(count3 == (n-1)) {
                printf("\n");
            }
        }
    }

    /* O loop do jogo principal */
    while(morto == 0 || N_casas_abertas < n * m - z) {
        printf("Bem-vindo ao caca-Minas!");









    }


    return 0;
}

