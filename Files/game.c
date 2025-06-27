#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "perguntas.h"
#include "game.h"

#define TOTAL_QUESTOES 15

int selecionar_por_nivel(Perguntas* perguntas, int quantidade, int nivel, int* usados) {
    int tentativas = 0;
    while (tentativas < 1000) {
        int i = rand() % quantidade;
        if (!usados[i] && perguntas[i].nivel == nivel) {
            usados[i] = 1;
            return i;
        }
        tentativas++;
    }
    return -1; 
}

void iniciar_partida(Perguntas* perguntas, int quantidade) {
    Perguntas selecionadas[TOTAL_QUESTOES];
    int* usados = calloc(quantidade, sizeof(int));
    if (!usados) {
        printf("Erro de memória.\n");
        return;
    }

    srand(time(NULL));

    int ordem_niveis[TOTAL_QUESTOES] = {
        1, 1,       
              2, 2,       
                     3, 3, 3, 3, 
                                 4, 4, 4, 4, 
                                            5,  5, 5     
    };

    for (int i = 0; i < TOTAL_QUESTOES; i++) {
        int indice = selecionar_por_nivel(perguntas, quantidade, ordem_niveis[i], usados);
        if (indice == -1) {
            printf("Erro: não há perguntas suficientes no nível %d.\n", ordem_niveis[i]);
            free(usados);
            return;
        }
        selecionadas[i] = perguntas[indice];
    }

    free(usados);

    int marco = 0;
    int i;

    for (i = 0; i < TOTAL_QUESTOES; i++) {
        Perguntas p = selecionadas[i];
        printf("\n  Pergunta %d (Nível %d):\n%s\n", i + 1, p.nivel, p.enunciado);
        printf("A) %s\nB) %s\nC) %s\nD) %s\nE) %s\n", 
            p.alternativas[0], p.alternativas[1],
            p.alternativas[2], p.alternativas[3],
            p.alternativas[4]);

        char resposta;
        printf("Digite sua resposta (A-E): ");
        scanf(" %c", &resposta);

        if (resposta == p.correta) {
            printf(" Resposta correta!!!\n");

            if (i == 4 || i == 9) {
                marco = i + 1;
                printf("Você atingiu um MARCO DE SEGURANÇA ! (%d perguntas)!\n", marco);
            }

        } else {
            printf(" Resposta incorreta....  A correta era %c.\n", p.correta);
            break;
        }
    }

    if (i == TOTAL_QUESTOES) {
        printf("\n Parabéns jogador!!!  Você ganhou R$ 1.000.000,00!\n");
    } else if (marco > 0) {
        printf("\n Você errou ... . mas garantiu o marco de segurança (%d perguntas).\n", marco);
    } else {
        printf("\n Que pena :cc , Você saiu sem nada. Boa sorte na próxima tentativa !\n");
    }
}
