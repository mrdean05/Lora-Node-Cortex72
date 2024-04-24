<h2> LoRaWAN end-device stack implementation for ARM Cortex-A72 processor running on Linux <h2>

## Introduction

This project is an implementation of a LoRaWAN end device stack for ARM Cortex-A72 processor running on Linux. This stack enables data communication between the end node and the things network through a LoRaWAN gateway. The end node hardware components includes an sx1262 lora module which interface via SPI and an PCAL6416A I/O expander which communicates with the SoC via I2C.

This also includes an open source code (`../src/lorawan.c`, `../src/boards/sx1262-board.c` and `../src/boards/radio-board.c`).

The [Porting Guide](https://stackforce.github.io/LoRaMac-doc/LoRaMac-doc-v4.7.0/_p_o_r_t_i_n_g__g_u_i_d_e.html) used in the implementation of the lora node stack.


## Hardware Connection


##  Get Started
- Clone the public repository

```bash
$ git clone https://github.com/mrdean05/Lora-Node-Cortex72.git
```

- Initialize submodules contained in the project
```bash
$ cd Lora-Node-Cortex72
$ git submodule update --init
```

- Follow the [link](https://www.waveshare.com/wiki/SX1302_LoRaWAN_Gateway_HAT) to check out how to set up a lorawan gateway and set up your credentials on the things network. The necessary credentials for OTAA (Over-The-Air-Activation) include Device EUI, APP EUI  and APP Key. 

- Include the credentials in (`../examples/send_receive_otaa/config.h`)

- Seed into the `../examples/send_receive_otaa/` and run the make file. 
```bash
$ cd examples/send_receive_otaa
$ make
```
- Run the executable file
```bash 
$ cd ../../build
$ ./a72_lorawan_hello_otaa
```

## Documents
PCAL6416A data sheet: [Link](https://www.nxp.com/docs/en/data-sheet/PCAL6416A.pdf)
SX1262 module datasheet: [Link] (https://www.mouser.com/datasheet/2/761/DS_SX1261-2_V1.1-1307803.pdf)

