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
 * @brief Aguarda os dados da função thread_recv e chama a função mandarRequisicao() para enviar uma requisição.
 * @return Um ponteiro para uma cadeia de caracteres contendo os dados.
 * @see mandarRequisicao()
 */
char* aguardarDados(void);

/**
 * @brief Manda uma requisição GET
 * @param sock ponteiro para um SOCKET definido previamente.
 * @param req string da requisição
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