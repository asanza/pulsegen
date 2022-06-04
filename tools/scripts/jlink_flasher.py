#!/usr/bin/env python3

'''
File: jlink_flasher.py

Copyright (c) 2019 Diego Asanza <f.asanza@gmail.com>

SPDX-License-Identifier: Apache-2.0
'''

import argparse
import pylink

if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Flash a file using JLink')

    parser.add_argument('-select', default='USB')
    parser.add_argument('-iface', default='SWD', help='SWD or JTAG interface')
    parser.add_argument('-speed', default='auto',
                        help='Interface speed or auto')
    parser.add_argument('-jlinkpath', default=None, help='Path to jlink tools')
    parser.add_argument('-address', default=0x08000000,
                        help='Memory address where to load the file')
    parser.add_argument(
        'file', help='binary file path. Only .bin, .hex and .elf supported')

    required = parser.add_argument_group('required named arguments')
    required.add_argument(
        '-device', help='Microcontroller device. See JLINK Doc', required=True)

    args = parser.parse_args()

    jlink = pylink.JLink()
    try:
        jlink.open()
    except Exception as ex:
        print("Error: {}".format(ex))
        exit(-1)

    if args.iface.upper() == 'SWD':
        jlink.set_tif(pylink.enums.JLinkInterfaces.SWD)
    elif args.iface.upper() == 'JTAG':
        jlink.set_tif(pylink.enums.JLinkInterfaces.JTAG)
    else:
        print('Error: Unsupported interface {}'.format(args.iface))
        exit(-1)

    jlink.connect(args.device)
    jlink.set_reset_strategy(pylink.enums.JLinkResetStrategyCortexM3.CONNECT_UNDER_RESET)
    jlink.reset()
    jlink.flash_file(args.file, args.address)
    jlink.reset()
    jlink.close()
    exit(0)
