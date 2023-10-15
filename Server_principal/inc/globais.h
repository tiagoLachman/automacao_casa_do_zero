/**
 * @file globais.h
 * @author Tiago André Lachman (tiagolachman@gmail.com)
 * @brief
 * @version 0.1
 * @date 19-02-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef GLOBAIS_H
#define GLOBAIS_H

// #define ATIVAR_CONSOLE_LOG

#ifdef ATIVAR_CONSOLE_LOG
#define PRINT_ERRO(text, err_id) (printf("\nERRO \"%s\":%d\n", text, err_id))
#define PRINT(text, ...) (printf(text, ##__VA_ARGS__))
#define APAGAR_TELA() (system("cls"))

#else
#define PRINT_ERRO(text, err_id) (text, err_id)
#define PRINT(text, ...) (text)
#define APAGAR_TELA()
#endif  // SEM_CONSOLE_LOG

#endif  // GLOBAIS_H