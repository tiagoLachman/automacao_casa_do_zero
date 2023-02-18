#ifndef HTTP_H
#define HTTP_H

#ifdef _WIN32_WINNT
//#undef _WIN32_WINNT

#error "_WIN32_WINNT já está definido"
#endif//_WIN32_WINNT

#define _WIN32_WINNT 0x0501

#include <stdio.h>
#include <winsock2.h>

DWORD WINAPI thread_recv(LPVOID data);

int dadosRecebidos(void);

int iniciarConexao(SOCKET* sock);

int conectarRemoto(SOCKET* sock, char* ipRemoto, u_short porta);

char* aguardarDados(void);

void resetarFlag(void);

int mandarRequisicao(SOCKET* sock, char* req, int len_req);

int criarServidor(SOCKET* sock, u_short port);

DWORD WINAPI thread_server(LPVOID data);
#endif//HTTP_H