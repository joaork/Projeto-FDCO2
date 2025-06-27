#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perguntas.h"
#include "funcoes.h"
#include "menu.h"
#include "game.h"
#include "raylib.h"
#include "raygui.h"

int menu(Perguntas* perguntas, int quantidade) {

    // Inicialização
    const int screenWidth = 1280;
    const int screenHeight = 720;
    int nivel;

    InitWindow(screenWidth, screenHeight, "Jogo do Milhão - Músicas Brasileiras");

    // Inicia áudio
    InitAudioDevice();
    Music musica = LoadMusicStream("showdomilhao8bit.mp3");
    PlayMusicStream(musica);

    // Carrega imagem de fundo
    Texture2D fundo = LoadTexture("fundo.png");
    if (fundo.id == 0) {
        TraceLog(LOG_ERROR, "Erro ao carregar imagem de fundo!");
        CloseWindow();
        return 1;
    }

    // Botões
    const int botaoLargura = 300;
    const int botaoAltura = 50;
    int botaoX = (screenWidth - botaoLargura) / 2;
    int botaoYInicial = (screenHeight - (4 * botaoAltura + 3 * 20)) / 2;

    const char *botoes[4] = {
        "Jogar uma partida",
        "Listar perguntas por nível",
        "Exportar perguntas para CSV",
        "Sair"
    };

    Rectangle retangulos[4];
    for (int i = 0; i < 4; i++) {
        retangulos[i] = (Rectangle){ botaoX, botaoYInicial + i * (botaoAltura + 20), botaoLargura, botaoAltura };
    }

    // Estilo dos botões
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x0000FFFF);
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0xFFA500FF);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0xC06000FF);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 0xFFFFFFFF);
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, 0xFFFFFFFF);
    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, 0xFFFFFFFF);

    SetTargetFPS(60);

    // Loop principal
    while (!WindowShouldClose()) {
        UpdateMusicStream(musica);

        BeginDrawing();
            // Desenha fundo
            DrawTexture(fundo, 0, 0, WHITE);

            // Texto de introdução
            DrawText("Bem-vindo ao Jogo do Milhão! Tema: Músicas Brasileiras", 80, 30, 24, BLACK);

            for (int i = 0; i < 4; i++) {
                if (GuiButton(retangulos[i], botoes[i])) {
                    switch (i) {
                        case 0:
                        iniciar_partida(perguntas, quantidade);
                                    
                            break;
                        case 1:
                            printf("Digite o nível (1 a 5): ");
                            scanf("%d", &nivel);
                            listar_por_nivel(perguntas, quantidade, nivel);
                            break;
                        case 2:
                            exportar_perguntas_csv("perguntas_exportadas.csv", perguntas, quantidade);
                            break;
                        case 3:
                            StopMusicStream(musica);
                            UnloadMusicStream(musica);
                            UnloadTexture(fundo);
                            CloseAudioDevice();
                            CloseWindow();
                            return 0;
                    }
                }
            }

        EndDrawing();
    }

    // Encerramento (caso saia pelo ESC)
    StopMusicStream(musica);
    UnloadMusicStream(musica);
    UnloadTexture(fundo);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}