#include <stdio.h>
#include <string.h>
#include "funcoes.h"
#include "perguntas.h"

Perguntas* carregar_perguntas_csv(const char* arquivoPath, int* quantidade){
FILE* f = fopen(arquivoPath,"r");
if(!f){
    perror("Erro ao abrir arquivo para write.\n");
        return NULL;
}
    Perguntas* perguntas = NULL;



}


void salvar_perguntas_binario(const char* arquivoPath, Perguntas* perguntas, int quantidade){







}


Perguntas* carregar_perguntas_binario(const char* arquivoPath, int* quantidade){




}


void exportar_perguntas_csv(const char* arquivoPath, Perguntas* perguntas, int quantsidade){





}


void listar_por_nivel(Perguntas* perguntas, int quantidade, Nivel nivel){








}