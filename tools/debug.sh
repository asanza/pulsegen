#!/usr/bin/env bash


if [ "$OS" = "Windows_NT " ]; then
openocd -f tools/debug.openocd &
cmd.exe /C "start cmd.exe /C arm-none-eabi-gdb -x tools/gdb.init"
else
set -m
openocd -f tools/debug.openocd >openocd.log 2>&1 &
openocdpid=$!
set +m
bash -c "arm-none-eabi-gdb -x tools/gdb.init"
fi
