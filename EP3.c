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


int tabuleiro[90][90][10];
int N_casas_abertas = 0;
int casas_abertas[90][90];
int N_casas_marcadas = 0;
int casas_marcadas[90][90];

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

void zera_arrays(int m, int n) {
    int zero1 = 0;
    int zero2 = 0;
    int zero3 = 0;

    for (zero1 = 0; zero1 < m; zero1++) {
        for (zero2 = 0; zero2 < n; zero2++) {
            for (zero3 = 0; zero3 < 10; zero3++) {
                tabuleiro[zero1][zero2][zero3] = 0;
            }
            casas_abertas[zero1][zero2] = 0;
            casas_marcadas[zero1][zero2] = 0;
        }
    }
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



void calcula_adjacentes(int m, int n) {
    int count2 = 0;
    int count3 = 0;

    for (count2 = 0; count2 < m; count2++) {
        for (count3 = 0; count3 < n; count3++) {
            int minas_adjacentes = 0;
            int loop = 1;

            if(count2 == 0 && count3 == 0) {
                tabuleiro[count2][count3][LESTE] = tabuleiro[count2][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUDESTE] = tabuleiro[count2 +1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUL] = tabuleiro[count2 + 1][count3][CENTRO];

                tabuleiro[count2][count3][SUDOESTE] = -1;
                tabuleiro[count2][count3][OESTE] = -1;
                tabuleiro[count2][count3][NOROESTE] = -1;
                tabuleiro[count2][count3][NORTE] = -1;
                tabuleiro[count2][count3][NORDESTE] = -1;
            } else if (count2 == 0 && count3 == (n-1)) {
                tabuleiro[count2][count3][OESTE] = tabuleiro[count2][count3 - 1][CENTRO];
                tabuleiro[count2][count3][SUDOESTE] = tabuleiro[count2 + 1][count3 - 1][CENTRO];
                tabuleiro[count2][count3][SUL] = tabuleiro[count2 + 1][count3][CENTRO];

                tabuleiro[count2][count3][SUDESTE] = -1;
                tabuleiro[count2][count3][LESTE] = -1;
                tabuleiro[count2][count3][NORDESTE] = -1;
                tabuleiro[count2][count3][NORTE] = -1;
                tabuleiro[count2][count3][NOROESTE] = -1;
            } else if (count2 == (n-1) && count3 == (n-1)) {
                tabuleiro[count2][count3][NORTE] = tabuleiro[count2 - 1][count3][CENTRO];
                tabuleiro[count2][count3][NOROESTE] = tabuleiro[count2 - 1][count3 - 1][CENTRO];
                tabuleiro[count2][count3][OESTE] = tabuleiro[count2][count3 - 1][CENTRO];

                tabuleiro[count2][count3][SUDOESTE] = -1;
                tabuleiro[count2][count3][SUL] = -1;
                tabuleiro[count2][count3][SUDESTE] = -1;
                tabuleiro[count2][count3][LESTE] = -1;
                tabuleiro[count2][count3][NORDESTE] = -1;
            } else if (count2 == (n-1) && count3 == 0) {
                tabuleiro[count2][count3][NORTE] = tabuleiro[count2 - 1][count3][CENTRO];
                tabuleiro[count2][count3][NORDESTE] = tabuleiro[count2 - 1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][LESTE] = tabuleiro[count2][count3 + 1][CENTRO];

                tabuleiro[count2][count3][SUDESTE] = -1;
                tabuleiro[count2][count3][SUL] = -1;
                tabuleiro[count2][count3][SUDOESTE] = -1;
                tabuleiro[count2][count3][OESTE] = -1;
                tabuleiro[count2][count3][NOROESTE] = -1;
            } else if (count2 == 0 && count3 != 0 && count3 != (n-1)) {
                tabuleiro[count2][count3][LESTE] = tabuleiro[count2][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUDESTE] = tabuleiro[count2 + 1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUL] = tabuleiro[count2 + 1][count3][CENTRO];
                tabuleiro[count2][count3][SUDOESTE] = tabuleiro[count2 + 1][count3 - 1][CENTRO];
                tabuleiro[count2][count3][OESTE] = tabuleiro[count2][count3 - 1][CENTRO];

                tabuleiro[count2][count3][NOROESTE] = -1;
                tabuleiro[count2][count3][NORTE] = -1;
                tabuleiro[count2][count3][NORDESTE] = -1;
            } else if (count2 != 0 && count2 != (n-1) && count3 == 0) {
                tabuleiro[count2][count3][NORTE] = tabuleiro[count2 - 1][count3][CENTRO];
                tabuleiro[count2][count3][NORDESTE] = tabuleiro[count2 - 1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][LESTE] = tabuleiro[count2][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUDESTE] = tabuleiro[count2 + 1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][SUL] = tabuleiro[count2 + 1][count3][CENTRO];

                tabuleiro[count2][count3][SUDOESTE] = -1;
                tabuleiro[count2][count3][OESTE] = -1;
                tabuleiro[count2][count3][NOROESTE] = -1;
            } else if (count2 == (n-1) && count3 != 0 && count3 != (n-1)) {
                tabuleiro[count2][count3][OESTE] = tabuleiro[count2][count3 - 1][CENTRO];
                tabuleiro[count2][count3][NOROESTE] = tabuleiro[count2 - 1][count3 - 1][CENTRO];
                tabuleiro[count2][count3][NORTE] = tabuleiro[count2 - 1][count3][CENTRO];
                tabuleiro[count2][count3][NORDESTE] = tabuleiro[count2 - 1][count3 + 1][CENTRO];
                tabuleiro[count2][count3][LESTE] = tabuleiro[count2][count3 + 1][CENTRO];

                tabuleiro[count2][count3][SUDESTE] = -1;
                tabuleiro[count2][count3][SUL] = -1;
                tabuleiro[count2][count3][SUDOESTE] = -1;
            } else if (count2 != 0 && count2 != (n - 1) && count3 == (n-1)) {
                tabuleiro[count2][count3][SUL] = tabuleiro[count2 + 1][count3][CENTRO];
                tabuleiro[count2][count3][SUDOESTE] = tabuleiro[count2 + 1][count3 - 1][CENTRO];
                tabuleiro[count2][count3][OESTE] = tabuleiro[count2][count3 - 1][CENTRO];
                tabuleiro[count2][count3][NOROESTE] = tabuleiro[count2 - 1][count3 - 1][CENTRO];
                tabuleiro[count2][count3][NORTE] = tabuleiro[count2 - 1][count3][CENTRO];

                tabuleiro[count2][count3][NORDESTE] = -1;
                tabuleiro[count2][count3][LESTE] = -1;
                tabuleiro[count2][count3][SUDESTE] = -1;
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
                if (tabuleiro[count2][count3][loop] >= 0) {
                    minas_adjacentes += tabuleiro[count2][count3][loop];
                }
                loop++;
            }

            tabuleiro[count2][count3][TOTAL] = minas_adjacentes;

        }
    }
}

void marcar(int i, int j, int z) {
    if (casas_abertas[i - 1][j - 1] == 1) {
        printf("Sem efeito.");
    } else {
        if (casas_marcadas[i - 1][j - 1] == 1) {
            printf("Sem efeito.");
        } else {
            if (N_casas_marcadas == z) {
                printf("Sem efeito");
            } else {
                N_casas_marcadas += 1;
                casas_marcadas[i - 1][j - 1] = 1;
            }
        }
    }
}

void desmarcar(int i, int j) {
    if(casas_abertas[i - 1][j - 1] == 1) {
        printf("Sem efeito.");
    } else {
        if (casas_marcadas[i - 1][j - 1] == 0) {
            printf("Sem efeito");
        } else {
            N_casas_marcadas -= 1;
            casas_marcadas[i - 1][j - 1] = 0;
        }
    }
}

void abrir(int i, int j) {
    if (casas_abertas[i][j] == 1) {
        printf("Sem efeito.");
    } else {
        if (tabuleiro[i][j][CENTRO] == 1) {
            printf("BOOOOM! Voce acaba de pisar numa mina!\n");
            N_casas_abertas += 1;
            casas_abertas[i][j] = 1;
        } else {
            N_casas_abertas += 1;
            casas_abertas[i][j] = 1;

            if(tabuleiro[i][j][TOTAL] == 0) {
                if (tabuleiro[i][j][NORTE] == 0 && casas_abertas[i - 1][j] == 0) {
                    abrir(i - 1, j);
                }
                if (tabuleiro[i][j][NORDESTE] == 0 && casas_abertas[i - 1][j + 1] == 0) {
                    abrir(i - 1, j + 1);
                }
                if (tabuleiro[i][j][LESTE] == 0 && casas_abertas[i][j + 1] == 0) {
                    abrir(i, j + 1);
                }
                if (tabuleiro[i][j][SUDESTE] == 0 && casas_abertas[i + 1][j + 1] == 0) {
                    abrir(i + 1, j + 1);
                }
                if (tabuleiro[i][j][SUL] == 0 && casas_abertas[i + 1][j] == 0) {
                    abrir(i + 1, j);
                }
                if (tabuleiro[i][j][SUDOESTE] == 0 && casas_abertas[i + 1][j - 1] == 0) {
                    abrir(i + 1, j - 1);
                }
                if (tabuleiro[i][j][OESTE] == 0 && casas_abertas[i][j - 1] == 0) {
                    abrir(i, j - 1);
                }
                if (tabuleiro[i][j][NOROESTE] == 0 && casas_abertas[i - 1][j - 1] == 0) {
                    abrir(i - 1, j - 1);
                }                
            }
        }
    }
}

int comando_de_entrada(char a[1], int i, int j, int linha_maxima, int coluna_maxima) {
    if (i < 1 || i > linha_maxima || j < 1 || j > coluna_maxima) {
        return 0;
    } else {
        if (a[0] == 'A' || a[0] == 'a') {
            return 1;
        } if (a[0] == 'M' || a[0] == 'm') {
            return 2;
        } if (a[0] == 'D' || a[0] == 'd') {
            return 3;
        }
        return 0;
    }
}

/* retorna 0 se o jogo continua; 1 se o jogador venceu; 2 se o jogador perdeu */
int status_do_jogo(int T[MMAX][NMAX], int m, int n, int z) {
    int count1 = 0;
    int count2 = 0;

    for (count1 = 0; count1 < m; count1++) {
        for (count2 = 0; count2 < n; count2++) {
            if(T[count1][count2] == -1 && casas_abertas[count1][count2] == 1) {
                return 2;
            }
        }
    }

    if (N_casas_abertas == (m * n - z)) {
        return 1;
    }

    return 0;
}

int main() {
    int m = 0; /*numero de linhas*/
    int n = 0; /*numero de colunas*/
    int z = 0; /*numero de minas*/
    int seed = 0;
    int T[90][90];

    int resultado_do_jogo = 0;

    /* Variaveis de Loop */
    int count = 1;
    int count2 = 0;
    int count3 = 0;
    /*********************/

    entrada(&m, &n, &z, &seed);
    printf("%d %d %d %d \n", m, n, z, seed);

    /* Zera todo o array tabuleiro, casas_abertas e casas_marcadas */
    zera_arrays(m, n);

    /* Gera o tabuleiro e suas solucoes */
    while (count <= z) {
        int posicao_linha = posicao_linha_aleatoria(m, &seed);
        int posicao_coluna = posicao_coluna_aleatoria(m, n, &seed);

        novo_seed(&seed);
        if(tabuleiro[posicao_linha - 1][posicao_coluna - 1][CENTRO] != 1) {
            tabuleiro[posicao_linha - 1][posicao_coluna - 1][CENTRO] = 1; 
            count++;           
        }
    }

    /* Calcula quais e quantas posições adjacentes possuem mina */
    calcula_adjacentes(m, n);

    /* Associa, como pedido, um valor no tabuleiro:
        -1, se tem uma mina na posição;
        numero de minas adjacentes, se não tem;
    */
    for (count2 = 0; count2 < m; count2++) {
        for (count3 = 0; count3 < n; count3++) {
            if (tabuleiro[count2][count3][CENTRO] != 1) {
                T[count2][count3] = tabuleiro[count2][count3][TOTAL];
            } else {
                T[count2][count3] = -1;
            }
        }
    }
    

    printf("Bem-vindo ao Caca-Minas!\n");

    while(resultado_do_jogo == 0) {
        char comando[1];

        int linha;
        int coluna;
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
                        printf("  *");
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

        printf("Proximo chute: ");

        while (leitura_feita == 0) {
            int retorno = scanf("%s %d %d", comando, &linha, &coluna);
            if (retorno == 3 && comando_de_entrada(comando, linha, coluna, m, n) != 0) {
                leitura_feita = 1;
            } else {
                leitura_feita = 0;
            }
        }

        if (comando_de_entrada(comando, linha, coluna, m, n) == 1) {
            abrir(linha - 1, coluna - 1);
            resultado_do_jogo = status_do_jogo(T, m, n, z);
        } else if (comando_de_entrada(comando, linha, coluna, m, n) == 2) {
            marcar(linha, coluna, z);
            printf("Por enquanto: %d/%d marcadas, %d livres", N_casas_marcadas, z, (m * n - N_casas_abertas));
        } else if (comando_de_entrada(comando, linha, coluna, m, n) == 3) {
            desmarcar(linha, coluna);
            printf("Por enquanto: %d/%d marcadas, %d livres", N_casas_marcadas, z, (m * n - N_casas_abertas));
        }


    }


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
    (i, j, CENTRO) = 1, se tiver bomba
    (i, j, CENTRO) = 0, se não tiver bomba
    (i, j, OUTRAS_DIRECOES) = 1, se tiver bomba na direcao adjacente
    (i, j, OUTRAS_DIRECOES) = 0, se nao tiver bomba na direcao adjacente
    (i, j, OUTRAS_DIRECOES) = -1, se nao existir uma posicao naquela direcao
    (i, j, TOTAL) = numero total de bombas adjacentes

NA MATRIZ T
    (i, j) = -1, se tiver uma mina no local
    (i, j) = numero total de minas adjacentes, se não tiver uma mina no local clicado





*/