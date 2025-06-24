#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"
#include "perguntas.h"


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
    printf("Foi possivel salvar perguntas em binário , prosseguindo...\n\n"); //i <3 debugging with printf
}


Perguntas* carregar_perguntas_binario(const char* arquivoPath, int* quantidade){
    FILE* f = fopen(arquivoPath,"rb");
    if(!f){ perror("Não foi possivel ler o binario.\n"); 
        return NULL; }

        fread(quantidade,sizeof(int),1,f); //lendo o endereço de qtd considerando que o parametro é * 
        Perguntas* perguntas = malloc(*quantidade * sizeof(Perguntas)); //criando vetor alocado da quantidade lida
        fread(perguntas,sizeof(Perguntas),*quantidade,f); //lendo para o vetor criado 
        fclose(f);
        printf("Foi possivel carregar perguntas em binario, prosseguindo....\n"); //i <3 debugging with printf
        return perguntas;
}


void exportar_perguntas_csv(const char* arquivoPathCsv, Perguntas* perguntas, int quantidade){
 FILE* arquivo = fopen(arquivoPathCsv, "w");
    if (!arquivo) {
        perror("Erro ao abrir arquivo CSV para escrita");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",%c,%d\n", //formatação do csv conforme o layout
            perguntas[i].enunciado, //enunciado
            perguntas[i].alternativas[0],
            perguntas[i].alternativas[1],
            perguntas[i].alternativas[2],
            perguntas[i].alternativas[3],
            perguntas[i].alternativas[4], //alternativas
            perguntas[i].correta, //alter correta
            perguntas[i].nivel //o lvl 
        );
    }

    fclose(arquivo);
    printf("Perguntas exportadas com sucesso para %s , prosseguindo....\n", arquivoPathCsv);
}


void listar_por_nivel(Perguntas* perguntas, int quantidade, Nivel nivel){
  printf("Perguntas do nível %d:\n", nivel); //com base no parametro recebido na main do enum , vai listar ( aquele bgl de vEasy,med,hard,etc,etc)
    for (int i = 0; i < quantidade; i++) {
        if (perguntas[i].nivel == nivel) {
            printf("Q%d: %s\n", i+1, perguntas[i].enunciado);
            for (int j = 0; j < 5; j++) {
                printf("  %c) %s\n", 'A'+j, perguntas[i].alternativas[j]);
            }
            printf("Resposta correta  : %c\n\n", perguntas[i].correta); //exib da correta
        }
    }
}