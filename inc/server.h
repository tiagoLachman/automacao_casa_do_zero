#ifndef SERVER_H
#define SERVER_H

/**
 * @brief Estrutura de dados de uma requisição
 * 
 */
typedef struct{
    char* tipo;
    char* cod;
    char* path;
    char* content_length;
    char* data;
}req_dados;

/**
 * @brief Trata os dados de uma requisição.
 * 
 * @param req dados da requisição.
 * @return req_dados resposta que o servidor dará ao cliente.
 */
req_dados server_res_handle(req_dados* req);

/**
 * @brief Altera os dados que vem em uma string para uma struct mais fácil de lidar.
 * 
 * @param dados dados da requisição HTTP em string.
 * @return req_dados dados já separados em uma struct.
 */
req_dados* server_char_para_req(char *dados);



#endif//SERVER_H