/**
 * @file http.c
 * @author Tiago André Lachman (tiagolachman@gmail.com)
 * @brief
 * @version 0.1
 * @date 19-02-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <globais.h>
#include <http.h>
#include <server.h>
#include <string_fort.h>
#include <ws2tcpip.h>

int flagRecv;
int sizeRecv;
char server_reply[10000];

DWORD WINAPI thread_recv(LPVOID data) {
    SOCKET sock = (SOCKET)data;
    while (1) {
        if (flagRecv != 1) {
            if ((sizeRecv = recv(sock, server_reply, 10000, 0)) == SOCKET_ERROR) {
                int err = WSAGetLastError();
                PRINT("\nRECV: %d\n", err);
                return err;
            }
            flagRecv = sizeRecv > 0;
        }
    }
    return 0;
}

DWORD WINAPI sub_thread_server(LPVOID data) {
    SOCKET sock = (SOCKET)data;
    int bytes_recv = 0;
    char* string_recv;
    string_recv = (char*)malloc(sizeof(char) * 1024);
    DWORD returnVal = 0;

    if ((bytes_recv = recv(sock, string_recv, 1024, 0)) == SOCKET_ERROR) {
        int err = WSAGetLastError();
        PRINT("\nRECV_SERVER: %d\n", err);
        if (err == WSAECONNABORTED) {
            PRINT("\nConexão abortada\n");
        }
        returnVal = 1;
        goto exit_sub_thread_server;
    }
    
    server_res_handle(server_char_para_req(string_recv));
    const char* const_res = "HTTP/1.1 200 OK\r\n\r\n asd";
    PRINT("Sending client res:%s\n", const_res);

    if (send(sock, const_res, strlen(const_res), 0) == SOCKET_ERROR) {
        PRINT("\nSEND_SERVER:%d\n", WSAGetLastError());
        returnVal = 1;
        goto exit_sub_thread_server;
    }
exit_sub_thread_server:
    free(string_recv);
    closesocket(sock);
    return returnVal;
}

DWORD WINAPI thread_server(LPVOID data) {
    SOCKET sock = (SOCKET)data;
    SOCKET client;
    struct sockaddr_in ipCliente;
    int len_ipCliente = sizeof(ipCliente);
    // HANDLE thread_server_HANDLE;

    while (1) {
        client = accept(sock, (struct sockaddr*)&ipCliente, &len_ipCliente);
        CreateThread(NULL, 0, sub_thread_server, (LPVOID)client, 0, NULL);
    }
    return 0;
}

int dadosRecebidos(void) {
    return flagRecv;
}

void resetarFlag(void) {
    flagRecv = 0;
}

char* aguardarDados(void) {
    while (dadosRecebidos() != 1) {
    }
    server_reply[sizeRecv] = '\0';
    resetarFlag();
    return server_reply;
}

int iniciarConexao(SOCKET* sock) {
    WSADATA wsa;

    PRINT("Inicializando winsock...");

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        int err = WSAGetLastError();
        if (err != WSAEINPROGRESS) return err;
    }
    PRINT("Iniciou WSA\n");

    if ((*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        return WSAGetLastError();
    }
    PRINT("Iniciou Socket\n");

    return 0;
}

int conectarRemoto(SOCKET* sock, char* hostname, char* porta) {
    struct addrinfo ip_dns, *ptr = NULL, *result = NULL;
    int conReturn;

    ZeroMemory(&ip_dns, sizeof(ip_dns));
    ip_dns.ai_family = AF_UNSPEC;
    ip_dns.ai_socktype = SOCK_STREAM;
    ip_dns.ai_protocol = IPPROTO_TCP;

    conReturn = getaddrinfo(hostname, porta, &ip_dns, &result);
    if (conReturn != 0) {
        PRINT("getaddrinfo failed: %d\n", conReturn);
        WSACleanup();
        return 1;
    }

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        *sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (*sock == INVALID_SOCKET) {
            PRINT("Error at socket(): %d\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            return 1;
        }

        // Connect to server.
        conReturn = connect(*sock, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (conReturn == SOCKET_ERROR) {
            closesocket(*sock);
            *sock = INVALID_SOCKET;
            continue;
        }
        break;
    }
    PRINT("Conexao estabelecida");

    CreateThread(NULL, 0, thread_recv, (LPVOID)*sock, 0, NULL);

    return 0;
}

int mandarRequisicao(SOCKET* sock, char* req, int len_req) {
    char* msg = "GET  HTTP/1.1\r\nAuthorization: Basic MTIzOjEyMw==\r\n\r\n";
    msg = (char*)malloc(sizeof(char) * len_req + strlen(msg) * sizeof(char) + 1);

    sprintf(msg, "GET %s HTTP/1.1\r\nAuthorization: Basic MTIzOjEyMw==\r\n\r\n", req);

    if (send(*sock, msg, strlen(msg), 0) < 0) {
        return WSAGetLastError();
    }

    return 0;
}

int criarServidor(SOCKET* sock, u_short port) {
    int err = iniciarConexao(sock);
    if (err != 0) {
        return err;
    }
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;
    local.sin_port = htons(port);

    err = bind(*sock, (struct sockaddr*)&local, sizeof(local));
    if (err != 0) {
        return err;
    }

    err = listen(*sock, 10);
    if (err != 0) {
        return err;
    }

    CreateThread(NULL, 0, thread_server, (LPVOID)*sock, 0, NULL);

    return 0;
}