```
/**
*　　　　　　 ＿＿
*　　　　　／＞　　フ
*　　　　　| 　_　 _l
*　 　　　／` ミ＿xノ
*　　 　 /　　　 　 |
*　　　 /　 ヽ　　 ﾉ
*　 　 │　　|　|　|
*　／￣|　　 |　|　|
*　| (￣ヽ＿_ヽ_)__)
*　＼二つ
*/
```

# README

## Introduction

This is a repo maintained by Bryan to share some useful embedded related
code. You can send the feedback by applying new
issue using Gitlab or sending email to <zhubeilife@gmail.com>

## Structure

```

├── bitband.h                       ------ Using bitband to control GPIO example
├── bsp                             ------ Chip related lib
│   ├── 74hc4067.c                     --- 16-Channel Analog Multiplexer/Demultiplexer
│   ├── 74hc4067.h                     --- 16-Channel Analog Multiplexer/Demultiplexer
│   ├── lm75.c                         --- LM75x Digital Temperature Sensor
│   ├── lm75.h                         --- LM75x Digital Temperature Sensor
│   ├── mcp3421.c                      --- 18-Bit Analog-to-Digital Converter with I2C
│   ├── mcp3421.h                      --- 18-Bit Analog-to-Digital Converter with I2C
│   ├── tle8108em.c                    --- 8-Channel Low Side Relay with SPI Interface
│   └── tle8108em.h                    --- 8-Channel Low Side Relay with SPI Interface
├── can_filter.c                    ------ CAN Filter Set Example
├── dwt_delay.c                     ------ Using DWT to provide a delay in ms
├── dwt_delay.h                     ------ Using DWT to provide a delay in ms
├── README.md                       ------ Readme Documents
├── retarget.c                      ------ Different ways to retarget printf()
├── syscalls                        ------ Collecting different syscalls implements
│   ├── AC6_syscalls.c                 --- collecting from AC6/System Workbench
│   └── MasterSTM32_retarget.c         --- collecting form book "Master STM32"
├── template                        ------ Doxygen examples
│   ├── Doxyfile                       --- doxygen settings
│   ├── mytemplate.c                   --- template source file
│   └── mytemplate.h                   --- template header file
└── XFormatPrintf                   ------ Another implementations of Printf C
    ├── example.c                      --- examples of using it
    ├── xformatc.c                     --- xformat source file
    └── xformatc.h                     --- xformat header file

```
