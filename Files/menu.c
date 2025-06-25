#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perguntas.h"
#include "funcoes.h"
#include "menu.h"
#include "game.h"

void menu(Perguntas* perguntas, int quantidade) {
    int opcao;

    do {
        printf("\n==== JOGO DO MILHÃO ====\n");
        printf("1. Jogar uma partida\n");
        printf("2. Listar perguntas por nível\n");
        printf("3. Exportar perguntas para CSV\n"); // opcional
        printf("4. Sair\n");
        printf("Escolha uma opção:\n ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                iniciar_partida(perguntas, quantidade);
                break;
            case 2:{
                int nivel;
                printf("Digite o nível (1 a 5): ");
                scanf("%d", &nivel);
                listar_por_nivel(perguntas, quantidade, nivel);
                break;
            }
            case 3:
                exportar_perguntas_csv("perguntas_exportadas.csv", perguntas, quantidade);
                break;
            case 4:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 4);
}


