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

    #define MSG_TAM 256
    char mensagem[MSG_TAM] = "";
    bool mostrarMensagem = false;
    int timerMensagem = 0;

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
                        // Tela para escolher o nível
                        bool escolhendoNivel = true;
                        nivel = 1; // valor padrão

                        while (escolhendoNivel && !WindowShouldClose()) {
                            BeginDrawing();
                            ClearBackground(RAYWHITE);

                            DrawText("Escolha um nível para listar as perguntas:", 300, 100, 24, DARKGREEN);

                            // Botões de nível
                            for (int n = 1; n <= 5; n++) {
                                Rectangle botaoNivel = { 300 + (n - 1) * 120, 200, 100, 50 };
                                char textoBotao[16];
                                sprintf(textoBotao, "Nível %d", n);
                                if (GuiButton(botaoNivel, textoBotao)) {
                                    nivel = n;
                                    escolhendoNivel = false;
                                }
                            }

                            EndDrawing();
                        }

                        // Chama a tela Raylib com as perguntas do nível escolhido
                        listar_por_nivel(perguntas, quantidade, nivel);
                            break;
                        case 2:
                            exportar_perguntas_csv("perguntas_exportadas.csv", perguntas, quantidade, mensagem, MSG_TAM);
                                mostrarMensagem = true;
                                timerMensagem = 180; // ~3 segundos a 60fps
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

            if (mostrarMensagem) {
                int caixaLargura = MeasureText(mensagem, 20) + 40;
                int caixaAltura = 50;
                int caixaX = (screenWidth - caixaLargura) / 2;
                int caixaY = screenHeight - 100;

                DrawRectangle(caixaX, caixaY, caixaLargura, caixaAltura, Fade(LIGHTGRAY, 0.85f));
                DrawRectangleLines(caixaX, caixaY, caixaLargura, caixaAltura, DARKGRAY);
                DrawText(mensagem, caixaX + 20, caixaY + 15, 20, DARKGREEN);

                timerMensagem--;
                if (timerMensagem <= 0) {
                    mostrarMensagem = false;
                    mensagem[0] = '\0';
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