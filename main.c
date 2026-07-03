#include <avr/io.h>
#include <util/delay.h>
#include "config.h"
#include "usart.h"


typedef enum {
    MODE_SERIAL,
    MODE_WIRELESS
} ComMode;


ComMode modo_ativo;

void System_Init(void) {
    // Configura o pino de seleção de modo como entrada com resistor de pull-up interno
    clr_bit(COM_MODE_DDR, COM_MODE_PIN);
    set_bit(COM_MODE_PORT, COM_MODE_PIN);
    
    // Pequeno delay para estabilização das tensões dos pinos
    _delay_ms(10);
    
    // Leitura do pino de configuração para decidir a versão de comunicação
    // Se o pino estiver em nível lógico ALTO (1), assume modo Serial. Se em BAIXO (0), Wireless.
    if (tst_bit(COM_MODE_PINX, COM_MODE_PIN)) {
        modo_ativo = MODE_SERIAL;
        USART_Init(9600); // Inicializa a USART a 9600 bps
    } else {
        modo_ativo = MODE_WIRELESS;
        // Aqui entrará a inicialização do módulo sem fio futuramente
    }
}

int main(void) {
    // Inicializa os periféricos base e define o modo de comunicação
    System_Init();
    
    // Mensagem inicial de depuração (caso esteja no modo Serial)
    if (modo_ativo == MODE_SERIAL) {
        USART_SendString("--- Data-Logger Inteligente Inicializado (Modo Serial) ---\r\n");
    }

    /* Loop principal de operação contínua */
    while (1) {
        
        // 1. Ler Sensores Analógicos (Temperatura e LDR)
        // TODO: Implementar leitura do ADC
        
        // 2. Aplicar Filtro Passa-Baixas Digital
        // TODO: Implementar filtro exponencial ou média móvel
        
        // 3. Ler Sensores Digitais (Umidade e Chuva)
        // TODO: Implementar leitura dos pinos digitais
        
        // 4. Obter Timestamp do RTC
        // TODO: Implementar leitura via I2C/TWI
        
        // 5. Transmitir Dados pela interface selecionada
        if (modo_ativo == MODE_SERIAL) {
            // Transmissão via USART (Exemplo temporário)
            USART_SendString("Coletando e enviando dados via cabo...\r\n");
        } else {
            // Transmissão via Módulo Sem Fio
            // TODO: Implementar envio wireless
        }
        
        // Intervalo entre as coletas de dados (Ex: 2 segundos para fins de teste)
        _delay_ms(2000);
    }
    
    return 0; // O programa nunca deve chegar aqui
}
