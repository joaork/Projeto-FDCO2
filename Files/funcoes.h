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
#include "perguntas.h" //struct das perguntas. 

/**
 * @brief carrega perguntas do arquivo .csv
 * 
 * @param arquivo 
 * @param perguntas 
 * @param max 
 * @return int 
 */
int carregar_perguntas(const char arquivo, Perguntas perguntas[], int max);

/**
 * @brief exibe as perguntas.
 * 
 * @param p 
 */
void exibir_pergunta(const Perguntas *p);

/**
 * @brief verifica a resposta do usuario.
 * 
 * @param p 
 * @param resposta_usuario 
 * @return int 
 */
int verificar_resposta(const Perguntas *p, char resposta_usuario);

#endif // QUIZ_H