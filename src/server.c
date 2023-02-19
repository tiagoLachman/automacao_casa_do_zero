/**
 * @file server.c
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
#include <stdio.h>
#include <winsock2.h>
// #pragma comment(lib,"ws2_32.lib") //Winsock Library

int timeOut = 5000;

int main() {
    SOCKET sock;
    iniciarConexao(&sock);

    // Conectando-se ao ip de destino
    conectarRemoto(&sock, "esp01_quarto", "80");

    char *msg_on = "/on";
    char *msg_off = "/off";

    mandarRequisicao(&sock, msg_on, strlen(msg_on));
    printf("\nAguardando dados...\n%s\n", aguardarDados());

    mandarRequisicao(&sock, msg_off, strlen(msg_off));
    printf("Aguardando dados...\n%s\n", aguardarDados());

    SOCKET server;
    if (criarServidor(&server, (u_short)7012) != 0) {
        PRINT_ERRO("erro ao criar o server");
    }

    while (1) {
    }
    closesocket(sock);
    closesocket(server);
    WSACleanup();

    system("pause");
    return 0;
}