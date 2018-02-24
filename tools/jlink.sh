#!/usr/bin/env bash

if [ "$OS" = "Windows_NT" ]; then
JLinkGDBServerCL.exe -select USB -device STM32F107RC -if JTAG -speed auto -noir  -port 3333 -singlerun -rtos GDBServer/RTOSPlugin_FreeRTOS&
cmd.exe /C "start cmd.exe /C arm-none-eabi-gdb -x tools/gdb.init"
else
set -m
JLinkGDBServer -select USB -device STM32F107RC -if JTAG -speed auto -noir  -port 3333 -singlerun -rtos GDBServer/RTOSPlugin_FreeRTOS>jlink.log 2>&1 &
jlinkpid=$!
set +m
bash -c "arm-none-eabi-gdb -x tools/gdb.init -tui"
fi
