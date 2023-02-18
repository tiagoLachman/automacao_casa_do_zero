#include <http.h>
#include <stdio.h>
#include <winsock2.h>

//#pragma comment(lib,"ws2_32.lib") //Winsock Library

int timeOut = 5000;

int main(int argc, char* argv[]) {
    SOCKET sock;
    iniciarConexao(&sock);

    // Conectando-se ao ip de destino
    conectarRemoto(&sock, "esp01_quarto", "80");

    char *msg_on = "/on";
    char *msg_off = "/off";

finish:;

    mandarRequisicao(&sock, msg_on, strlen(msg_on));
    printf("\nAguardando dados...\n%s\n", aguardarDados());

    mandarRequisicao(&sock, msg_off, strlen(msg_off));
    printf("Aguardando dados...\n%s\n", aguardarDados());

    SOCKET server;
    criarServidor(&server, (u_short)7012);
    while(1){

    }
    closesocket(sock);
    WSACleanup();
    
    system("pause");
    return 0;
}