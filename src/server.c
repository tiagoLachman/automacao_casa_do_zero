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


/*
TODO: Melhorar a parte do http, somente retornar quando o content-length for alcançado.
TODO: Refazer a parte do server_char_para_req, deixar realmente funcionando.
*/

#include <globais.h>
#include <http.h>
#include <server.h>
#include <stdio.h>
#include <string_fort.h>
#include <winsock2.h>
// #pragma comment(lib,"ws2_32.lib") //Winsock Library

int timeOut = 5000;

req_dados server_char_para_req(char *dados) {
    req_dados req;
    system("cls");
    printf("\nserver_char_para_req:\n%s", dados);

    return req;
}

req_dados server_res_handle(req_dados req) {
    printf("\nreq.tipo:%s\nreq.path:%s\n", req.tipo, req.path);
    req_dados res;

    res.data = (char*)malloc(sizeof(char) * 5);
    sprintf(res.data, "vtc");
    return res;
}

int main() {
    int err = 0;
    SOCKET sock;
    if ((err = iniciarConexao(&sock)) != 0) {
        PRINT_ERRO(err);
    }

    // Conectando-se ao ip de destino
    if ((err = conectarRemoto(&sock, "esp01_quarto", "80")) != 0) {
        PRINT_ERRO(err);
    }
    char *msg_on = "/on";
    char *msg_off = "/off";

    if ((err = mandarRequisicao(&sock, msg_on, strlen(msg_on))) != 0) {
        PRINT_ERRO(err);
    }
    printf("\nAguardando dados...\n%s\n", aguardarDados());

    if ((err = mandarRequisicao(&sock, msg_off, strlen(msg_off))) != 0) {
        PRINT_ERRO(err);
    }
    printf("Aguardando dados...\n%s\n", aguardarDados());

    SOCKET server;
    if ((err = criarServidor(&server, (u_short)7012)) != 0) {
        PRINT_ERRO(err);
    }

    while (1) {
    }
    closesocket(sock);
    closesocket(server);
    WSACleanup();

    system("pause");
    return 0;
}