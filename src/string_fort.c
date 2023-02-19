#include <stdlib.h>
#include <string.h>
#include <string_fort.h>

char* substring(char* c, int inicio, int fim) {
    if (fim < inicio) return "";
    char* ret = malloc(sizeof(char) * (fim - inicio));

    for (int i = inicio; i <= fim; i++) {
        ret[i - inicio] = c[i];
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

    if (key_fim != 0x18) {
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
