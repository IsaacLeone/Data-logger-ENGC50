#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "config.h"
#include "usart.h"
#include "adc.h"
#include "filter.h"
#include "rtc.h"
#include "digital_sensor.h"
#include "wireless.h"

typedef enum {
    MODE_SERIAL,
    MODE_WIRELESS
} ComMode;

ComMode modo_ativo;

// Instâncias dos filtros digitais para os canais analógicos
EMA_Filter filtro_temp;
EMA_Filter filtro_ldr;

void System_Init(void) {
    // Configura pino de seleção de modo
    clr_bit(COM_MODE_DDR, COM_MODE_PIN);
    set_bit(COM_MODE_PORT, COM_MODE_PIN);
    _delay_ms(10);
    
    // Inicialização dos Periféricos de Entrada
    ADC_Init();
    I2C_Init();
    DigitalSensors_Init();
    
    // Decide e inicializa o canal exclusivo de comunicação
    if (tst_bit(COM_MODE_PINX, COM_MODE_PIN)) {
        modo_ativo = MODE_SERIAL;
        USART_Init(9600);
    } else {
        modo_ativo = MODE_WIRELESS;
        Wireless_Init();
    }
}

int main(void) {
    System_Init();
    
    char buffer_saida[128];
    DateTime agora;
    
    if (modo_ativo == MODE_SERIAL) {
        USART_SendString("--- Data-Logger Pronto (Modo Serial Ativo) ---\r\n");
    }

    while (1) {
        // 1. Leitura dos Sensores Analógicos (Brutos)
        uint16_t raw_temp = ADC_Read(0); // Canal ADC0
        uint16_t raw_ldr  = ADC_Read(1); // Canal ADC1
        
        // 2. Aplicação do Filtro Digital Passa-Baixas
        float temp_filtrada = Filter_Update(&filtro_temp, raw_temp);
        float ldr_filtrado  = Filter_Update(&filtro_ldr, raw_ldr);
        
        // 3. Leitura dos Sensores Digitais
        uint8_t chuva = Read_RainSensor();
        uint8_t umidade = Read_HumiditySensor();
        
        // 4. Captura do Horário Real do RTC
        RTC_GetTime(&agora);
        
        // 5. Formatação da String de Dados (Formato CSV para reconstrução histórica)
        snprintf(buffer_saida, sizeof(buffer_saida),
                 "[%02d/%02d/%04d %02d:%02d:%02d] T_raw:%d T_fil:%.1f L_raw:%d L_fil:%.1f Chuva:%d Umid:%d",
                 agora.day, agora.month, agora.year, agora.hour, agora.minute, agora.second,
                 raw_temp, (double)temp_filtrada, raw_ldr, (double)ldr_filtrado, chuva, umidade);
                 
        // 6. Transmissão Exclusiva conforme escolha inicial do Usuário
        if (modo_ativo == MODE_SERIAL) {
            USART_SendString(buffer_saida);
            USART_SendString("\r\n");
        } else {
            Wireless_SendData(buffer_saida);
        }
        
        // Intervalo de amostragem de campo (2 segundos para avaliação em bancada)
        _delay_ms(2000);
    }
    return 0;
}
