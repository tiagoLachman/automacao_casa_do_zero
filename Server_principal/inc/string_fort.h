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

#define SEM_ASCII 0x18

/**
 * @brief Corta uma string.
 * @param c string a ser cortada.
 * @param inicio index do inicio do corte.
 * @param fim index do fim do corte.
 * @return char* Ponteiro de um malloc com a string cortada.
 */
char* substring(char* c, int inicio, int fim);

/**
 * @brief Corta uma string, inicio é um valor numérico e o final é um caractere
 *
 * @param c string a ser cortada
 * @param inicio index do inicio do corte
 * @param fim caractere de para de corte
 * @return char* Ponteiro de um malloc com a string cortada.
 */
char* substring_int_char(char* c, int inicio, char fim);

/**
 * @brief Procura uma string em outra string, retorna, se encotrado, a "key" até o "key_fim".
 * @param res string a ser procurada.
 * @param key string a ser encontrada.
 * @param key_fim Caracter de fim, caso "0x18" retorna só a key.
 * @return char* Ponteiro de um malloc com a string cortada.
 */
char* procurar_substring(char* res, char* key, char key_fim);

/**
 * @brief Corta uma string, inicio e fim são definidos por um caractere.
 *
 * @param c string a ser cortada
 * @param inicio caractere index de inicio
 * @param fim caractere index de fim
 * @return char* Ponteiro de um malloc com a string cortada.
 */
char* substring_char_char(char* c, char inicio, char fim);

#endif  // STRING_FORT_H