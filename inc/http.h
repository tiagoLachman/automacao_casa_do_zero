#ifndef HTTP_H
#define HTTP_H

#ifdef _WIN32_WINNT
// #undef _WIN32_WINNT

#error "_WIN32_WINNT já está definido"
#endif  //_WIN32_WINNT

#define _WIN32_WINNT 0x0501

#include <stdio.h>
#include <winsock2.h>

/**
 * @brief Inicializa as configurações para realizar conexões.
 * @param sock ponteiro para um SOCKET definido previamente.
 * @return 0 se ocorrer tudo bem.
 */
int iniciarConexao(SOCKET* sock);

/**
 * @brief Conecta a um servidor remoto
 * @param sock ponteiro para um SOCKET definido previamente.
 * @param hostname deve ser um hostname e não um IP
 * @param porta porta da conexão
 * @return 0 se tudo bem
 */
int conectarRemoto(SOCKET* sock, char* hostname, char* porta);

/**
 * @brief Aguarda os dados da função thread_recv
 * @param void
 * @return char* contendo os dados.
 */
char* aguardarDados(void);

/**
 * @brief Manda uma requisição GET
 * @param sock ponteiro para um SOCKET definido previamente.
 * @param req IP da requisição
 * @param len_req tamanho de req
 * @return 0 se tudo bem.
 */
int mandarRequisicao(SOCKET* sock, char* req, int len_req);

/**
 * @brief Cria um servidor
 * @param sock ponteiro para um SOCKET definido previamente.
 * @param port porta do servidor.
 * @return 0 se tudo bem.
*/
int criarServidor(SOCKET* sock, u_short port);

#endif  // HTTP_H