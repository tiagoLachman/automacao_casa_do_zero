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
#include <string.h>
// #pragma comment(lib,"ws2_32.lib") //Winsock Library

int timeOut = 5000;

req_dados *server_char_para_req(char *dados) {
    req_dados *req = (req_dados *)malloc(sizeof(req_dados));
    APAGAR_TELA();
    req->cod = "";
    req->data = "";
    req->tipo = "";
    req->path = "";
    req->content_length = "";

    PRINT("\nHTTP request:%s\n", dados);

    size_t len = strcspn(dados, " ");
    req->tipo = (char *)malloc(sizeof(char) * (len + 1));
    memcpy(req->tipo, dados, len);
    req->tipo[len] = '\0';

    dados += len + 1;
    len = strcspn(dados, " ");
    req->path = (char *)malloc(sizeof(char) * (len + 1));
    memcpy(req->path, dados, len);
    req->path[len] = '\0';

    return req;
}

req_dados server_res_handle(req_dados *req) {
    printf("\nreq.tipo:%s\nreq.path:%s\n", req->tipo, req->path);
    req_dados res;

    res.data = (char *)malloc(sizeof(char) * 5);
    sprintf(res.data, "vtc");
    return res;
}

int main() {
    int err = 0;
    SOCKET_novo sock;

    if ((err = iniciarConexao(&sock)) != 0) {
        PRINT_ERRO("iniciarConexao()", err);
    }

    // Conectando-se ao ip de destino
    if ((err = conectarRemoto(&sock, "esp01_quarto", "80")) != 0) {
        PRINT_ERRO("conectarRemoto()", err);
    }
    char *msg_on = "/on";
    char *msg_off = "/off";

    sock.parametros_conexao = "Authorization: Basic MTIzOjEyMw==";

    if ((err = mandarRequisicao(&sock, msg_on, strlen(msg_on))) != 0) {
        PRINT_ERRO("mandarRequisicao()", err);
    }
    PRINT("\nAguardando dados...\n%s\n", aguardarDados(sock));

    if ((err = mandarRequisicao(&sock, msg_on, strlen(msg_off))) != 0) {
        PRINT_ERRO("mandarRequisicao()", err);
    }

    PRINT("Aguardando dados...\n%s\n", aguardarDados(sock));

    SOCKET_novo server;
    server.sock_status = status_desconfigurado;
    if ((err = criarServidor(&server, (u_short)7012)) != 0) {
        PRINT_ERRO("criarServidor()", err);
    }

    int op = 0;
    while (err == 0) {
        system("cls");
        printf("op:%d\ndigitado:", op);
        scanf("%d", &op);
        iniciarConexao(&sock);
        conectarRemoto(&sock, "esp01_quarto", "80");
        if (op == 1) {
            if ((err = mandarRequisicao(&sock, msg_on, strlen(msg_on))) != 0) {
                printf("\nmandarRequisicao(msg_on):%d\n", err);
            }
        } else {
            if ((err = mandarRequisicao(&sock, msg_off, strlen(msg_off))) != 0) {
                printf("\nmandarRequisicao(msg_off):%d\n", err);
            }
        }
        printf("Aguardando dados...\n%s\n", aguardarDados(sock));
        closesocket(sock.sock);
        system("pause");
    }

    PRINT_ERRO("while(err == 0)", err);
    fechar_socket(sock);
    fechar_socket(server);
    WSACleanup();

    system("pause");
    return 0;
}