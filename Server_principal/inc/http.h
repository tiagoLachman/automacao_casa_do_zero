/**
 * @file http.h
 * @author Tiago André Lachman (tiagolachman@gmail.com)
 * @brief 
 * @version 0.1
 * @date 19-02-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef HTTP_H
#define HTTP_H

#ifdef _WIN32_WINNT
// #undef _WIN32_WINNT

#error "_WIN32_WINNT já está definido"
#endif  //_WIN32_WINNT

#define _WIN32_WINNT 0x0501

#include <stdio.h>
#include <winsock2.h>

typedef enum{
    status_desconfigurado = -2,
    status_configurado = -1,
    status_conectado = 0,
    status_server,
    status_cliente
}socket_estado;

typedef struct{
    SOCKET sock;
    socket_estado sock_status;
    char* parametros_conexao;
}SOCKET_novo;

/**
 * @brief Inicializa as configurações para realizar conexões.
 * @param sock ponteiro para um SOCKET definido previamente.
 * @return 0 se ocorrer tudo bem.
 */
int iniciarConexao(SOCKET_novo* sock);

/**
 * @brief Conecta a um servidor remoto
 * @param sock ponteiro para um SOCKET definido previamente.
 * @param hostname deve ser um hostname e não um IP
 * @param porta porta da conexão
 * @return 0 se tudo bem
 */
int conectarRemoto(SOCKET_novo* sock, char* hostname, char* porta);

/**
 * @brief Aguarda os dados da função thread_recv e chama a função mandarRequisicao() para enviar uma requisição.
 * @param sock Ponteiro para o socket que se deseja aguardar os dados
 * @return Um ponteiro para uma cadeia de caracteres contendo os dados.
 * @see mandarRequisicao()
 */
char* aguardarDados(SOCKET_novo sock);

/**
 * @brief Manda uma requisição GET
 * @param sock ponteiro para um SOCKET definido previamente.
 * @param req string da requisição
 * @param len_req tamanho de req
 * @return 0 se tudo bem.
 */
int mandarRequisicao(SOCKET_novo* sock, char* req, int len_req);


/**
 * @brief Cria um servidor
 * @param sock ponteiro para um SOCKET definido previamente.
 * @param port porta do servidor.
 * @return 0 se tudo bem.
*/
int criarServidor(SOCKET_novo* sock, u_short port);

/**
 * @brief Alternativa para o closesocket(), por causa do SOCKET_novo.
 * 
 * @param sock Socket a ser fechado
 */
void fechar_socket(SOCKET_novo sock);


#endif  // HTTP_H