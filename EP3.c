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

#define MMAX 90
#define NMAX 90

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
        printf("Numero de minas (1 <= z <= 15): ");
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


int main() {
    int m = 0; /*numero de linhas*/
    int n = 0; /*numero de colunas*/
    int z = 0; /*numero de minas*/
    int seed = 0;

    entrada(&m, &n, &z, &seed);
    return 0;
}
