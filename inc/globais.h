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

#define ATIVAR_CONSOLE_LOG

#ifdef ATIVAR_CONSOLE_LOG
#define PRINT_ERRO(text)    (printf("\nERRO:%d\n", text))
#define PRINT(text, ...)    (printf(text, ##__VA_ARGS__))

#else 
#define PRINT_ERRO(text)    (text)
#define PRINT(text, ...)    (text)

#endif//SEM_CONSOLE_LOG

#endif//GLOBAIS_H