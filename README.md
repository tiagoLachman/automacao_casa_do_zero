# Automacao de uma casa do zero

Sistema de automação residencial feito em C no windows, utilizando uma placa de prototipagem ESP01 com um sensor de tensão integrado para controle de lampadas e um sistema integrador web feito em C para facilitar o acionamento e controle (também facilitando o anexo de sensores futuros).

## Status

- Realizado programa base de controle de relé com esp01;
- Server principal com a base do código;

## TODO

- Esp01_Relé:
  - Testar o programa base da ESP01 na placa;
  - Fazer update do schematic da placa após os testes;
  - Criar endpoint de "statusPlaca" com o máximo de dados possível para debug e análise;
  - Adicionar feedback da saída por algum sensor de corrente, exemplo ACS712;
- Server_principal:
  - Criar um DNS na rede para as placas ESP01;
  - Refatorar o código para os novos tipos de requisições;
  - Fazer comunicação com DB;
- Postman:
  - Criar variáveis de ambiente para as requisições;
  - Talvez um teste automatico das placas;
