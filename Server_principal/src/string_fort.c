/**
 * @file string_fort.c
 * @author Tiago André Lachman (tiagolachman@gmail.com)
 * @brief
 * @version 0.1
 * @date 19-02-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>
#include <string.h>
#include <string_fort.h>
#include <stdio.h>

char* substring(char* c, int inicio, int fim) {
    if (fim < inicio) return "";
    char* ret = (char*)malloc(sizeof(char) * (fim - inicio + 1));
    ret[fim - inicio] = '\0';
    for (int i = inicio; i < fim; i++) {
        ret[i - inicio] = c[i];
        c[i] = SEM_ASCII;
    }
    return ret;
}

char* procurar_substring(char* res, char* key, char key_fim) {
    int len_key = strlen(key);
    int k = 0, index = -1;
    int n = 0, i = 0;
    for (i = 0; i < (int)(strlen(res)); i++) {
        if (res[i] == key[k]) {
            k++;
            if (k >= len_key) {
                index = i - k + 1;
                break;
            }
        } else {
            k = 0;
        }
    }
    if (index < 0) return "";

    if (key_fim != SEM_ASCII) {
        for (i = index + len_key; i < (int)(strlen(res)); i++) {
            if (res[i] == key_fim) {
                n--;
                break;
            } else {
                n++;
            }
        }
    }
    return substring(res, index, index + len_key + n + 1);
}

char* substring_char_char(char* c, char inicio, char fim) {
    int nInicio = 0, nFim;
    while (c[nInicio] != inicio) nInicio++;

    nFim = nInicio;

    while (c[nFim] != fim) nFim++;
    return substring(c, nInicio, nFim);
}

char* substring_int_char(char* c, int inicio, char fim) {
    if (inicio < 0) return "";
    int nFim = inicio;
    while (c[nFim] != fim) nFim++;

    return substring(c, inicio, nFim);
}