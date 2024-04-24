<h2> LoRaWAN end-device stack implementation for ARM Cortex-A72 processor running on Linux <h2>

## 1.Introduction

This project is an implementation of a LoRaWAN end device stack for ARM Cortex-A72 processor running on Linux. This stack enables data communication between the end node and the things network through a LoRaWAN gateway. The end node hardware components includes an sx1262 lora module which interface via SPI and an PCAL6416A I/O expander which communicates with the SoC via I2C.

This also includes an open source code (`..\src\lorawan.c`, `..\src\boards\sx1262-board.c` and `..\src\boards\radio-board.c`).

The [Porting Guide](https://stackforce.github.io/LoRaMac-doc/LoRaMac-doc-v4.7.0/_p_o_r_t_i_n_g__g_u_i_d_e.html) used in the implementation of the lora node stack.


## 2. Hardware Connection


## 3. Get Started



