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
#define TOTAL 9


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
    *seed = rand() % 12345;
}

/* Retorna numero entre 1 e o maximo de linhas, inclusive */
int posicao_linha_aleatoria(int linhas, int *seed) {
    int numero = 0;

    srand(*seed);
    numero = rand();
    return numero % linhas + 1;
}

/* Retorna numero entre 1 e o maximo de colunas, inclusive */
int posicao_coluna_aleatoria(int linhas, int colunas, int *seed) {
    int numero = 0;

    srand(*seed);
    numero = rand();
    return (numero / linhas) % colunas + 1;
}

void borda_superior(int colunas) {
    int contagem = 1;
    printf("\n");
    printf("     ");
    for(contagem = 1; contagem <= colunas; contagem++) {
        printf("%3d", contagem);
    }
    printf("\n");
    printf("    +");
    for(contagem = 1; contagem <= colunas; contagem++) {
        printf("---");
    }
    printf("-+\n");

}

void borda_inferior(int colunas) {
    int contagem = 1;
    printf("    +");
    for(contagem = 1; contagem <= colunas; contagem++) {
        printf("---");
    }
    printf("-+\n");
    printf("     ");
    for(contagem = 1; contagem <= colunas; contagem++) {
        printf("%3d", contagem);
    }
    printf("\n");
}

int main() {
    int m = 0; /*numero de linhas*/
    int n = 0; /*numero de colunas*/
    int z = 0; /*numero de minas*/
    int seed = 0;
    int tabuleiro[90][90][10];
    int T[90][90];

    int morto = 0;
    int N_casas_abertas = 0;
    int casas_abertas[90][90];
    int N_casas_marcadas = 0;
    int casas_marcadas[90][90];

    /* Variaveis de Loop */
    int zero1 = 0;
    int zero2 = 0;
    int zero3 = 0;

    int count = 1;
    int count2 = 0;
    int count3 = 0;
    /*********************/

    entrada(&m, &n, &z, &seed);
    printf("%d %d %d %d \n", m, n, z, seed);

    /* Zera todo o vetor tabuleiro, casas_abertas e casas_marcadas */
    for (zero1 = 0; zero1 < m; zero1++) {
        for (zero2 = 0; zero2 < n; zero2++) {
            for (zero3 = 0; zero3 < 10; zero3++) {
                tabuleiro[zero1][zero2][zero3] = 0;
            }
            casas_abertas[zero1][zero2] = 0;
            casas_marcadas[zero1][zero2] = 0;
        }
    }

    casas_abertas[1][3] = 1;
    casas_abertas[2][4] = 1;
    casas_abertas[3][1] = 1;
    casas_marcadas[1][1] = 1;

    /* Gera o tabuleiro e suas solucoes */
    while (count <= z) {
        int posicao_linha = posicao_linha_aleatoria(m, &seed);
        int posicao_coluna = posicao_coluna_aleatoria(m, n, &seed);

        novo_seed(&seed);
        if(tabuleiro[posicao_linha - 1][posicao_coluna - 1][CENTRO] != -1) {
            tabuleiro[posicao_linha - 1][posicao_coluna - 1][CENTRO] = -1; 
            count++;           
        }
    }

    /* Calcula quais e quantas posições adjacentes possuem mina */
    for (count2 = 0; count2 < m; count2++) {
        for (count3 = 0; count3 < n; count3++) {
            int minas_adjacentes = 0;
            int loop = 1;

            if(count2 == 0 && count3 == 0) {
                tabuleiro[count2][count3][LESTE] = tabuleiro[count2][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUDESTE] = tabuleiro[count2 +1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUL] = tabuleiro[count2 + 1][count3][CENTRO];
            } else if (count2 == 0 && count3 == (n-1)) {
                tabuleiro[count2][count3][OESTE] = tabuleiro[count2][count3 - 1][CENTRO];
                tabuleiro[count2][count3][SUDOESTE] = tabuleiro[count2 + 1][count3 - 1][CENTRO];
                tabuleiro[count2][count3][SUL] = tabuleiro[count2 + 1][count3][CENTRO];
            } else if (count2 == (n-1) && count3 == (n-1)) {
                tabuleiro[count2][count3][NORTE] = tabuleiro[count2 - 1][count3][CENTRO];
                tabuleiro[count2][count3][NOROESTE] = tabuleiro[count2 - 1][count3 - 1][CENTRO];
                tabuleiro[count2][count3][OESTE] = tabuleiro[count2][count3 - 1][CENTRO];
            } else if (count2 == (n-1) && count3 == 0) {
                tabuleiro[count2][count3][NORTE] = tabuleiro[count2 - 1][count3][CENTRO];
                tabuleiro[count2][count3][NORDESTE] = tabuleiro[count2 - 1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][LESTE] = tabuleiro[count2][count3 + 1][CENTRO];
            } else if (count2 == 0 && count3 != 0 && count3 != (n-1)) {
                tabuleiro[count2][count3][LESTE] = tabuleiro[count2][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUDESTE] = tabuleiro[count2 + 1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUL] = tabuleiro[count2 + 1][count3][CENTRO];
                tabuleiro[count2][count3][SUDOESTE] = tabuleiro[count2 + 1][count3 - 1][CENTRO];
                tabuleiro[count2][count3][OESTE] = tabuleiro[count2][count3 - 1][CENTRO];
            } else if (count2 != 0 && count2 != (n-1) && count3 == 0) {
                tabuleiro[count2][count3][NORTE] = tabuleiro[count2 - 1][count3][CENTRO];
                tabuleiro[count2][count3][NORDESTE] = tabuleiro[count2 - 1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][LESTE] = tabuleiro[count2][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUDESTE] = tabuleiro[count2 + 1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUL] = tabuleiro[count2 + 1][count3][CENTRO];
            } else if (count2 == (n-1) && count3 != 0 && count3 != (n-1)) {
                tabuleiro[count2][count3][OESTE] = tabuleiro[count2][count3 - 1][CENTRO];
                tabuleiro[count2][count3][NOROESTE] = tabuleiro[count2 - 1][count3 - 1][CENTRO];
                tabuleiro[count2][count3][NORTE] = tabuleiro[count2 - 1][count3][CENTRO];
                tabuleiro[count2][count3][NORDESTE] = tabuleiro[count2 - 1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][LESTE] = tabuleiro[count2][count3 + 1][CENTRO];
            } else if (count2 != 0 && count2 != (n - 1) && count3 == (n-1)) {
                tabuleiro[count2][count3][SUL] = tabuleiro[count2 + 1][count3][CENTRO];
                tabuleiro[count2][count3][SUDOESTE] = tabuleiro[count2 + 1][count3 - 1][CENTRO];
                tabuleiro[count2][count3][OESTE] = tabuleiro[count2][count3 - 1][CENTRO];
                tabuleiro[count2][count3][NOROESTE] = tabuleiro[count2 - 1][count3 - 1][CENTRO];
                tabuleiro[count2][count3][NORTE] = tabuleiro[count2 - 1][count3][CENTRO];
            } else {
                tabuleiro[count2][count3][NORTE] = tabuleiro[count2 - 1][count3][CENTRO];
                tabuleiro[count2][count3][NORDESTE] = tabuleiro[count2 - 1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][LESTE] = tabuleiro[count2][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUDESTE] = tabuleiro[count2 + 1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUL] = tabuleiro[count2 + 1][count3][CENTRO];
                tabuleiro[count2][count3][SUDOESTE] = tabuleiro[count2 + 1][count3 - 1][CENTRO];
                tabuleiro[count2][count3][OESTE] = tabuleiro[count2][count3 - 1][CENTRO];
                tabuleiro[count2][count3][NOROESTE] = tabuleiro[count2 - 1][count3 - 1][CENTRO];
            }

            while (loop < 9) {
                minas_adjacentes += tabuleiro[count2][count3][loop];
                loop++;
            }

            tabuleiro[count2][count3][TOTAL] = (-1) * minas_adjacentes;

        }
    }

        /* Associa, como pedido, um valor no tabuleiro:
            -1, se tem uma mina na posição;
            numero de minas adjacentes, se não tem;
        */
    for (count2 = 0; count2 < m; count2++) {
        for (count3 = 0; count3 < n; count3++) {
            if (tabuleiro[count2][count3][CENTRO] != -1) {
                T[count2][count3] = tabuleiro[count2][count3][TOTAL];
            } else {
                T[count2][count3] = -1;
            }
        }
    }
    

    printf("Bem-vindo ao caca-Minas!\n");

    while(1) {
        char comando[100];
        int leitura_feita = 0;

        /* Mostra o tabuleiro atualizado */
        borda_superior(n);
        for (count2 = 0; count2 < m; count2++) {
            printf("%3d |", count2 + 1);
            for (count3 = 0; count3 < n; count3++) {
                if (casas_abertas[count2][count3] == 1) {
                    printf("%3d", T[count2][count3]);
                } else {
                    if (casas_marcadas[count2][count3] == 1) {
                        printf("  @");
                    } else {
                        printf("  .");
                    }
                }

                if (count3 == (n-1)) {
                    printf(" |%3d\n", count2 + 1);
                }
            }
        }
        borda_inferior(n);

        /* TESTE: MOSTRA MATRIZ CASAS ABERTAS */
        for (count2 = 0; count2 < m; count2++) {
            for (count3=0; count3 < n; count3++) {
                printf("%4d", T[count2][count3]);
                if (count3 == (n - 1)) {
                    printf("\n");
                }
            }
        }

        printf("Próximo chute: ");

        while (leitura_feita == 0) {
            int retorno = scanf("%s", comando);
            if (retorno != 1) {
                leitura_feita = 0;
            } else {
                leitura_feita = 1;
            }
        }

    }


    /*
    while(morto == 0 || N_casas_abertas < n * m - z) {
         Montagem da tabela: 
        int a = 1;
        for(a = 1; a <= )
        








    }
    */


    return 0;
}

/*
NA MATRIZ CASAS_ABERTAS
    (i, j) = 1, se a casa estiver aberta
    (i, j) = 0, se a casa estiver fechada

NA MATRIZ CASAS_MARCADAS
    (i, j) = 1, se a casa estiver marcada
    (i, j) = 0, se a casa estiver desmarcada

NA MATRIZ TABULEIRO
    (i, j, CENTRO) = -1, se tiver bomba
    (i, j, CENTRO) = 0, se não tiver bomba
    (i, j, OUTRAS_DIRECOES) = 1, se tiver bomba na direcao adjacente
    (i, j, OUTRAS_DIRECOES) = 0, se nao tiver bomba na direcao adjacente
    (i, j, TOTAL) = numero total de bombas adjacentes

NA MATRIZ T
    (i, j) = -1, se tiver uma mina no local
    (i, j) = numero total de minas adjacentes, se não tiver uma mina no local clicado





*/