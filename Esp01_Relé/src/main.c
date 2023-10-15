#include "user_interface.h"

uint32 ICACHE_FLASH_ATTR user_rf_cal_sector_set(void) {
    enum flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        case FLASH_SIZE_64M_MAP_1024_1024:
            rf_cal_sec = 2048 - 5;
            break;
        case FLASH_SIZE_128M_MAP_1024_1024:
            rf_cal_sec = 4096 - 5;
            break;
        default:
            rf_cal_sec = 0;
            break;
    }
    return rf_cal_sec;
}

#include "ets_sys.h"
#include "osapi.h"
#include "ip_addr.h"
#include "espconn.h"
#include "mem.h"
#include "gpio.h"
#include "spi_flash.h"

#define WIFI_SSID "UniaoFlasco"
#define WIFI_PASSWORD "perguntaalipracigana"
#define WEB_SERVER_PORT 80
#define LIMITE_NOME_LAMPADA 50

struct espconn web_server;
esp_tcp web_server_tcp;

static int8_t statusRele = 0;
static char *nomeLampada;

#define GPIO_PIN_RELE 0

#define DATA_FILE_NAME "/data.txt"

// Definições de constantes para operações de arquivo
#define O_RDONLY 0
#define O_CREAT 0x0200
#define O_WRONLY 0x0400

#define FLASH_SAVE_ADDRESS 0x7A000

// Função para salvar uma string na memória flash
void saveStringToFlash(const char *str, int len) {
    spi_flash_erase_sector(FLASH_SAVE_ADDRESS / SPI_FLASH_SEC_SIZE);
    spi_flash_write(FLASH_SAVE_ADDRESS, (uint32 *)str, len);
}

void readStringFromFlash(char *str, int len) {
    spi_flash_read(FLASH_SAVE_ADDRESS, (uint32 *)str, len);
}

void refresh_rele_status() {
    GPIO_OUTPUT_SET(GPIO_PIN_RELE, statusRele);
}

void ICACHE_FLASH_ATTR web_server_receive(void *arg, char *data, unsigned short length) {
    int8_t signalStrength = wifi_station_get_rssi();
    struct espconn *pesp_conn = arg;

    if (strncmp(data, "GET /rele", 9) == 0) {
        char *response = (char *)os_malloc(1024);
        if (response) {
            os_sprintf(response, "HTTP/1.0 200 OK\r\nContent-Type: application/json\r\n\r\n");

            char *params = strstr(data, "?");
            if (params) {
                params++;  // Avancar para ignorar o '?'
                char *param = strtok(params, "&");
                while (param) {
                    char *key = strtok(param, "=");
                    if (key) {
                        char *value = strtok(NULL, "=");
                        if (value) {
                            if (strcmp(key, "status") == 0) {
                                statusRele = atoi(value) >= 1;
                                refresh_rele_status();
                            }
                            if (strcmp(key, "nome") == 0) {
                                if (os_strlen(value) <= 0) {
                                } else if (nomeLampada) {
                                    int pos = LIMITE_NOME_LAMPADA - 1;
                                    char *index = strstr(value, "HTTP/1.1");
                                    if (index) {
                                        int temp = index - value;
                                        if (temp <= LIMITE_NOME_LAMPADA - 1 && temp > 0) pos = temp;
                                    }
                                    os_strncpy(nomeLampada, value, pos);
                                    nomeLampada[pos - 1] = '\0';
                                    os_printf("nomeLampada:%s\npos:%d", nomeLampada, pos);

                                    saveStringToFlash(nomeLampada, os_strlen(nomeLampada));
                                    readStringFromFlash(nomeLampada, os_strlen(nomeLampada));
                                } else {
                                    os_printf("Q bosta\n");
                                }
                                refresh_rele_status();
                            }
                        }
                    }
                    param = strtok(NULL, "&");
                }
            }

            // Retorne a resposta JSON
            os_sprintf(response + os_strlen(response), "{\"status_rele\":\"%s\"", statusRele == 0 ? "desligado" : "ligado");
            os_sprintf(response + os_strlen(response), ",\"nome_lampada\":\"%s\"}", nomeLampada);

            espconn_sent(pesp_conn, response, os_strlen(response));
            os_free(response);
            espconn_disconnect(pesp_conn);
        }
    } else {
        char *response = (char *)os_malloc(1024);
        if (response) {
            os_sprintf(response, "HTTP/1.0 200 OK\r\nContent-Type: application/json\r\n\r\n");

            int8_t signalStrength = wifi_station_get_rssi();

            os_sprintf(response + os_strlen(response), "{\"signal_strength\":%d}", signalStrength);

            espconn_sent(pesp_conn, response, os_strlen(response));

            os_free(response);
            espconn_disconnect(pesp_conn);
        }
    }
}

void wifi_event_handler(System_Event_t *event) {
    if (event->event == EVENT_STAMODE_GOT_IP) {
        espconn_regist_recvcb(&web_server, web_server_receive);
        espconn_accept(&web_server);

        os_printf("Endereço IP da ESP8266: %d.%d.%d.%d\n", IP2STR(&event->event_info.got_ip.ip));

        uint32_t cpu_freq = system_get_cpu_freq();
        os_printf("Frequência da CPU: %d MHz\n", cpu_freq);
    }
}

void init_spi_flash() {
    if (spi_flash_init() == SPI_FLASH_RESULT_OK) {
        os_printf("Memória flash inicializada.\n");
    } else {
        os_printf("Falha na inicialização da memória flash.\n");
    }
}

void user_init(void) {
    nomeLampada = (char *)os_malloc(LIMITE_NOME_LAMPADA);

    // init_spi_flash();

    wifi_set_sleep_type(NONE_SLEEP_T);
    wifi_set_opmode(STATION_MODE);
    struct station_config stationConf;
    os_memset(&stationConf, 0, sizeof(struct station_config));
    os_sprintf(stationConf.ssid, WIFI_SSID);
    os_sprintf(stationConf.password, WIFI_PASSWORD);
    wifi_station_set_config(&stationConf);
    wifi_set_event_handler_cb(wifi_event_handler);

    web_server.type = ESPCONN_TCP;
    web_server.state = ESPCONN_NONE;
    web_server.proto.tcp = &web_server_tcp;
    web_server.proto.tcp->local_port = WEB_SERVER_PORT;

    wifi_station_connect();
}
