#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perguntas.h"
#include "funcoes.h"
#include "menu.h"
#include "game.h"

//lembrar de eliminar os printf para debug no > funcoes.c 

//cuidado com a codificacao utf-8 ao rodar  o codigo no terminal/exe , chcp 65001 no powershell pra evitar aqueles bugs maniacos de nao exibir acentos
int main(){
    Perguntas* perguntas = NULL;
    int quantidade = 0; //parametro essencial pra leitura e manipulacao dos arq 

    perguntas = carregar_perguntas_binario("perguntas.bin",&quantidade); 
    if(!perguntas){
        printf("Arquivo binário não encontrado. Lendo CSV...\n");
        perguntas = carregar_perguntas_csv("perguntasjogo.csv", &quantidade);
        salvar_perguntas_binario("perguntas.bin", perguntas, quantidade);
        printf("Bem-vindo ao Jogo do Milhão ! ! O tema do jogo > Músicas Brasileiras. Esteja preparado pra ficar rico ( ou não ) ! \n"); //no terminal,antes de adaptar pro raylib.
    }
    printf("Bem-vindo ao Jogo do Milhão ! ! O tema do jogo > Músicas Brasileiras. Esteja preparado pra ficar rico ( ou não ) ! \n");

    menu(perguntas,quantidade); //menu temporario . a funcao sera integrada com raylib,apenas usando para teste comum das funcoes
   
    salvar_perguntas_binario("perguntas.bin",perguntas,quantidade); //conforme tudo correto , salvando em .bin

    printf("Tudo correto até aqui(ler perguntas,exportar,salvar,segmento do jogo ,etc) se essa mensagem veio depois de digitar 4(switchcase>4) , entao ta funcional.\n\n"); //i <3 debugging with printf
    
    free(perguntas); //limpando essa bomba
    return 0;
}