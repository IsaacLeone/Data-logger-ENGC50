#include "usart.h"
#include "config.h"

void USART_Init(unsigned long baud) {
    // Cálculo do valor do registrador UBRR baseado no clock e baud rate desejado
    unsigned int ubrr = (F_CPU / (16UL * baud)) - 1;
    
    // Configura o Baud Rate nos registradores UBRR0H e UBRR0L
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    
    // Habilita o Transmissor (TX) e o Receptor (RX)
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    
    // Configura o formato do frame: 8 bits de dados, 1 bit de parada (8N1)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void USART_Transmit(char data) {
    // Aguarda o buffer de transmissão ficar vazio (verificando o bit UDRE0)
    while (!(UCSR0A & (1 << UDRE0)));
    
    // Coloca o dado no buffer e envia
    UDR0 = data;
}

void USART_SendString(const char* str) {
    while (*str) {
        USART_Transmit(*str);
        str++;
    }
}
