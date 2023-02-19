#ifndef GLOBAIS_H
#define GLOBAIS_H

//#define SEM_CONSOLE_LOG

#ifndef SEM_CONSOLE_LOG
#define PRINT_ERRO(text)    (printf("\n%s\n", text))
#define PRINT(text, ...)    (printf(text, ##__VA_ARGS__))

#else 
#define PRINT_ERRO(text)    (text)
#define PRINT(text, ...)    (text)

#endif//SEM_CONSOLE_LOG

#endif//GLOBAIS_H