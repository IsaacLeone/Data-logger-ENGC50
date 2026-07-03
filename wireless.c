#include "wireless.h"
#include "usart.h" // Se o módulo utilizar comandos UART físicos em pinos alternativos
#include <util/delay.h>

void Wireless_Init(void) {
    // Espaço para configuração dos pinos de controle do módulo de RF (ex: CE, CSN de rádio SPI)
    // Ou comandos de inicialização AT (se for baseado em UART)
}

void Wireless_SendData(const char* payload) {
    // Abstração de envio: dependendo do hardware escolhido pelo grupo,
    // os dados são empacotados aqui dentro de frames específicos do protocolo de rádio.
    
    // Exemplo de stub para simulação: redireciona os dados simulando saída RF
    USART_SendString("[RF TX]: ");
    USART_SendString(payload);
    USART_SendString("\r\n");
}
