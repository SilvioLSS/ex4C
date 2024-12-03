#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 10

struct tabuleiros {
    int jogado;
    int posicao;
};

void preencherTabuleiro(struct tabuleiros tab[]) {
    srand(time(NULL));

    // Inicializando todas as posições do tabuleiro com 0 (água).
    int i;
    for (i = 0; i < TAM; i++) {
        tab[i].posicao = 0;
        tab[i].jogado = 0;
    }

    // Posicionando os navios na metade do tabuleiro.
    for (i = 0; i < TAM / 2; i++) {
        tab[rand() % 10].posicao = 1;
    }

    // Posicionando uma bomba em uma posição que não esteja um navio.
    int bomba;
    for (i = 0; i < 1; i++) {
        bomba = rand() % 10;

        if (tab[bomba].posicao == 0) {
            tab[bomba].posicao = -1;
        } else {
            i--;
        }
    }
}

void imprimirTabuleiro(struct tabuleiros tab[]) {
    printf("\n");

    int i;
    for (i = 0; i < TAM; i++) {
        if (tab[i].jogado == 0) {
            printf("\t| |");
        }
        if (tab[i].jogado == 1) {
            printf("\t|X|");
        }
    }

    printf("\n");
}

void jogar(struct tabuleiros tab[], int *c) {
    int posicao;

    do {
        printf("\nDigite a posição que deseja realizar o disparo (de 1 a 10): \n");
        scanf("%d", &posicao);

        if (tab[posicao - 1].jogado == 1) {
            printf("\nVocê já jogou nessa posição. Digite outro número: \n");
        }

        if (posicao < 1 || posicao > 10) {
            printf("\nPosição inválida, digite um número de 1 a 10\n");
        }

    } while (posicao < 1 || posicao > 10 || tab[posicao - 1].jogado == 1);

    tab[posicao - 1].jogado = 1;

    if (tab[posicao - 1].posicao == -1) {
        printf("\nTinha uma bomba na posição %d. Você perdeu!\n", posicao);
        *c = 0;  
        return;
    }

    if (tab[posicao - 1].posicao == 1) {
        printf("\nVocê atingiu um navio na posição %d.\n", posicao);
        tab[posicao - 1].posicao = 0;  
    }
}

int verificarVitoria(struct tabuleiros tab[], int *c) {
    int i;
    for (i = 0; i < TAM; i++) {
        if (tab[i].posicao == 1) {
            return 1;
        }
    }
    return 0; 
}

int main() {
    int continuar = 1;

    struct tabuleiros tabuleiro[TAM];

    preencherTabuleiro(tabuleiro);

    do {
        imprimirTabuleiro(tabuleiro);
        jogar(tabuleiro, &continuar);
        if (verificarVitoria(tabuleiro, &continuar) == 0) {
            printf("\nVocê venceu o jogo!\n");
            return 0;
        }

    } while (continuar == 1);

    return 0;
}
