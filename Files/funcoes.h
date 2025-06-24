#ifndef FUNCOES_H
#define FUNCOES_H

/**
 * @file funcoes.h
 *
 * @brief Declarar as funcoes
 * @version 0.1
 * @date 2025-05-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "perguntas.h" //struct das perguntas ;


 //essencial saber a manipulação do >quantidade> na main , vai ser usado praticamente como parametro geral dos arquivos
Perguntas* carregar_perguntas_csv(const char* arquivoPath, int* quantidade);


void salvar_perguntas_binario(const char* arquivoPath, Perguntas* perguntas, int quantidade);


Perguntas* carregar_perguntas_binario(const char* arquivoPath, int* quantidade);


void exportar_perguntas_csv(const char* arquivoPathCsv, Perguntas* perguntas, int quantidade);


void listar_por_nivel(Perguntas* perguntas, int quantidade, Nivel nivel);


#endif // QUIZ_H
