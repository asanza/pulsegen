#!/usr/bin/env bash

qemu-system-gnuarmeclipse -M generic -mcu STM32F107VC -nographic \
    -monitor null -serial null -semihosting -semihosting-config \
     enable=on,target=native -s -S -kernel $1  2>&1