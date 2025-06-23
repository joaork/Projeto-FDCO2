#ifndef PERGUNTAS_H
#define PERGUNTAS_H

/**
 * @file perguntas.h
 * @brief PERGUNTAS DO JOGO DO MILHAO
 * @version 0.1
 * 
 */

 /**
  * @brief  Enum para nivel das perguntas.
  * 
  */

#define TAMANHO_ENUNCIADO 256
#define TAMANHO_RESPOSTA 100
// tamanhos para perguntas e repostas.

typedef enum{
    MUITO_FACIL=1, FACIL, MEDIO, DIFICIL, MUITO_DIFICIL
}Nivel;
/**
 * @brief struct para perguntas;
 * 
 */
typedef struct{
    char enunciado[TAMANHO_ENUNCIADO];
    char alt_a[TAMANHO_RESPOSTA], alt_b[TAMANHO_RESPOSTA], alt_c[TAMANHO_RESPOSTA], alt_d[TAMANHO_RESPOSTA], alt_e[TAMANHO_RESPOSTA];
    char correta;
    Nivel nivel;
}Perguntas;


#endif // QUIZ_H