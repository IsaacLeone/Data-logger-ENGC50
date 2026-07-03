#ifndef WIRELESS_H_
#define WIRELESS_H_

#include <stdint.h>

// Inicializa a interface de hardware sem fio
void Wireless_Init(void);

// Envia um pacote de strings via link de rádio
void Wireless_SendData(const char* payload);

#endif /* WIRELESS_H_ */
