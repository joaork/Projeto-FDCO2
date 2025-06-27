#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"
#include "perguntas.h"
#include "raylib.h"
#include "raygui.h"


#define MAX_LINHA 500

Perguntas* carregar_perguntas_csv(const char* arquivoPath, int* quantidade){
FILE* f = fopen(arquivoPath,"r");
if(!f){
    perror("Erro ao abrir arquivo para write.\n");
        return NULL;
}
    Perguntas* perguntas = NULL;
    char linhaLida[MAX_LINHA];
    int lidos = 0;
     
    
        while (fgets(linhaLida, MAX_LINHA, f)) {
        perguntas = realloc(perguntas, (lidos + 1) * sizeof(Perguntas)); //realocando a cada pergunta lida
        char* token = strtok(linhaLida, ","); //usando strtok pra quebrar a linha  e delimitando em subgrupos com ' , '
        
        strncpy(perguntas[lidos].enunciado, token, TAMANHO_ENUNCIADO); //lendo para a struct perguntas - o enunciado com base no token lido dest<-source<-quant

        for (int i = 0; i < 5; i++) {
            token = strtok(NULL, ",");
            strncpy(perguntas[lidos].alternativas[i], token, TAMANHO_RESPOSTA); //mesma ideia do enunciado,apenas com a diferença de usar o token delimitado por a ' , ' para ler as alternativas
        }

        token = strtok(NULL, ",");
        perguntas[lidos].correta = token[0]; //dando assign da correta para token[0]

        token = strtok(NULL, ",");
        perguntas[lidos].nivel = atoi(token); //lendo o enum nivel e castando para int com (atoi) func

        lidos++; //aumentando o contador de lidos até que MAX_LINHA seja atingida no fgets
    }

    fclose(f);
    *quantidade = lidos; //pointer pra quantidade de linhas(perguntas) lidas
    printf("Foi possível retornar a struct de perguntas lidas no csv , prosseguindo...\n\n"); //i <3 debugging with printf
    return perguntas; //retornando a struct de perguntas com base no csv lido ;
}



void salvar_perguntas_binario(const char* arquivoPath, Perguntas* perguntas, int quantidade){
    FILE* f = fopen(arquivoPath,"wb");
    if(!f){
        perror("Não foi possivel escrever o arquivo em binario.\n");
        return;
    }
    fwrite(&quantidade,sizeof(int),1,f); //salvando o endereço de quant 
    fwrite(perguntas,sizeof(Perguntas),quantidade,f);  //salvando a struct vetor de perguntas
    fclose(f);
}


Perguntas* carregar_perguntas_binario(const char* arquivoPath, int* quantidade){
    FILE* f = fopen(arquivoPath,"rb");
    if(!f){ perror("Não foi possivel ler o binario.\n"); 
        return NULL; }

        fread(quantidade,sizeof(int),1,f); //lendo o endereço de qtd considerando que o parametro é * 
        Perguntas* perguntas = malloc(*quantidade * sizeof(Perguntas)); //criando vetor alocado da quantidade lida
        fread(perguntas,sizeof(Perguntas),*quantidade,f); //lendo para o vetor criado 
        fclose(f);
        return perguntas;
}


void exportar_perguntas_csv(const char* arquivoPathCsv, Perguntas* perguntas, int quantidade, char* mensagem, int tam_msg) {
    FILE* arquivo = fopen(arquivoPathCsv, "w");
    if (!arquivo) {
        snprintf(mensagem, tam_msg, "Erro ao abrir arquivo %s!", arquivoPathCsv);
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%c,%d\n",
            perguntas[i].enunciado,
            perguntas[i].alternativas[0],
            perguntas[i].alternativas[1],
            perguntas[i].alternativas[2],
            perguntas[i].alternativas[3],
            perguntas[i].alternativas[4],
            perguntas[i].correta,
            perguntas[i].nivel);
    }

    fclose(arquivo);
    snprintf(mensagem, tam_msg, "Exportado para %s com sucesso!", arquivoPathCsv);
}

#include "raylib.h"
#include "raygui.h"
#include <string.h>
#include <stdio.h>

int listar_por_nivel(Perguntas* perguntas, int quantidade, int nivel) {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    Rectangle scrollPanel = { 50, 80, 1180, 500 };
    Rectangle content = { 0, 0, 1160, 1000 };
    Vector2 scroll = { 0, 0 };
    Rectangle view = { 0 };

    char buffer[8192] = "";
    char linha[1024];

    // Preenche buffer com perguntas do nível informado
    for (int i = 0; i < quantidade; i++) {
        if (perguntas[i].nivel == nivel) {
            snprintf(linha, sizeof(linha), "Q%d: %s\n", i + 1, perguntas[i].enunciado);
            strncat(buffer, linha, sizeof(buffer) - strlen(buffer) - 1);
            for (int j = 0; j < 5; j++) {
                snprintf(linha, sizeof(linha), "   %c) %s\n", 'A' + j, perguntas[i].alternativas[j]);
                strncat(buffer, linha, sizeof(buffer) - strlen(buffer) - 1);
            }
            snprintf(linha, sizeof(linha), "   Resposta correta: %c\n\n", perguntas[i].correta);
            strncat(buffer, linha, sizeof(buffer) - strlen(buffer) - 1);
        }
    }

    Rectangle botaoVoltar = { screenWidth / 2 - 100, 600, 200, 50 };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Perguntas do Nível %d", nivel), screenWidth / 2 - 170, 20, 30, DARKGREEN);

        GuiScrollPanel(scrollPanel, NULL, content, &scroll, &view);
        BeginScissorMode((int)view.x, (int)view.y, (int)view.width, (int)view.height);
        DrawTextEx(GetFontDefault(), buffer, 
                   (Vector2){scrollPanel.x + 10 - scroll.x, scrollPanel.y + 10 + scroll.y}, 20, 2, DARKGREEN);
        EndScissorMode();

        if (GuiButton(botaoVoltar, "Voltar")) {
            return 1;  // retorna para o menu
        }

        EndDrawing();
    }

    return 1;
}