#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define LORA_INT        22
#define LORA_MOSI       10
#define LORA_MISO       9
#define LORA_SCK        11
#define LORA_NSS        8
#define LORA_EN         P1_0
#define LORA_RXEN       P1_1
#define LORA_TXEN       P1_2
#define LORA_RST        P1_3
#define LORA_IO1        P1_4
#define LORA_IO2        P1_5
#define LORA_IO3        P1_6
#define LORA_BUSY       P1_7


#define BOARD_TCXO_WAKEUP_TIME                      0

void set_spi_cs_high(void);

#ifdef __cplusplus
}
#endif
#endif 


