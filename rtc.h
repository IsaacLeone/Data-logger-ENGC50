#ifndef RTC_H_
#define RTC_H_

#include <avr/io.h>

// Estrutura para armazenamento do carimbo de tempo (Timestamp)
typedef struct {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
} DateTime;

// Inicializa a interface I2C (TWI)
void I2C_Init(void);
// Rotinas básicas de barramento I2C
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t data);
uint8_t I2C_Read_ACK(void);
uint8_t I2C_Read_NACK(void);

// Lê os dados completos de tempo do módulo RTC
void RTC_GetTime(DateTime *dt);

#endif /* RTC_H_ */
