#include "digital_sensor.h"
#include "config.h"

void DigitalSensors_Init(void) {
    // Configura os pinos como entradas
    clr_bit(SENSOR_DDR, RAIN_PIN);
    clr_bit(SENSOR_DDR, HUMIDITY_PIN);
    
    // Ativa os resistores de pull-up internos se os sensores atuarem em dreno aberto / nível baixo ativo
    set_bit(SENSOR_PORT, RAIN_PIN);
    set_bit(SENSOR_PORT, HUMIDITY_PIN);
}

uint8_t Read_RainSensor(void) {
    // Retorna 1 se detectar chuva, caso contrário 0 (Inverte se for ativo em nível baixo)
    return (tst_bit(SENSOR_PINX, RAIN_PIN)) ? 0 : 1;
}

uint8_t Read_HumiditySensor(void) {

    return (tst_bit(SENSOR_PINX, HUMIDITY_PIN)) ? 1 : 0;
}
