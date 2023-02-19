/**
 * @file string_fort.h
 * @author Tiago André Lachman (tiagolachman@gmail.com)
 * @brief 
 * @version 0.1
 * @date 19-02-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef STRING_FORT_H
#define STRING_FORT_H

/**
 * @brief Corta uma string.
 * @param c string a ser cortada.
 * @param inicio index do inicio do corte.
 * @param fim index do fim do corte.
 * @return char* Ponteiro de um malloc.
*/
char* substring(char* c, int inicio, int fim);

/**
 * @brief Procura uma string em outra string, retorna, se encotrado, a "key" até o "key_fim".
 * @param res String a ser procurada.
 * @param key String a ser encontrada.
 * @param key_fim Caracter de fim, caso "" retorna só a key.
 * @return char* Ponteiro de um malloc.
*/
char* procurar_substring(char* res, char* key, char key_fim);

#endif//STRING_FORT_H