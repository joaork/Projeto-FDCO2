#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "perguntas.h"
#include "game.h"

#define TOTAL_QUESTOES 15

// Função auxiliar para embaralhar vetor
void embaralhar(Perguntas* vetor, int n) {
    srand(time(NULL));
    for (int i = 0; i < n - 1; i++) {
        int j = i + rand() % (n - i);
        Perguntas temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
    }
}

void iniciar_partida(Perguntas* perguntas, int quantidade) {
    Perguntas selecionadas[TOTAL_QUESTOES];
    int contador_nivel[6] = {0};  // níveis 1-5
    int limite_nivel[6] = {0, 2, 2, 4, 4, 3}; // ignorar índice 0

    int selecionadas_total = 0;

    // Seleciona perguntas dos níveis corretos
    for (int i = 0; i < quantidade && selecionadas_total < TOTAL_QUESTOES; i++) {
        int n = perguntas[i].nivel;
        if (n >= 1 && n <= 5 && contador_nivel[n] < limite_nivel[n]) {
            selecionadas[selecionadas_total++] = perguntas[i];
            contador_nivel[n]++;
        }
    }

    // Embaralha perguntas
    embaralhar(selecionadas, TOTAL_QUESTOES);

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

    // Resultado final
    if (i == TOTAL_QUESTOES) {
        printf("\n Parabéns jogador!!!  Você ganhou R$ 1.000.000,00!\n");
    } else if (marco > 0) {
        printf("\n Você errou .... mas garantiu o marco de segurança (%d perguntas).\n", marco);
    } else {
        printf("\n Que pena :cc , Você saiu sem nada. Boa sorte na próxima tentativa !\n");
    }
}
