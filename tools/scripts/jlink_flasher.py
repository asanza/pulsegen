#!/usr/bin/env python3

'''
File: jlink_flasher.py

Copyright (c) 2019 Diego Asanza <f.asanza@gmail.com>

SPDX-License-Identifier: Apache-2.0
'''

import subprocess
import argparse
import os
import re
import sys
import threading
from shutil import which
import time

jlink_gdbserver = 'JLinkGDBServer'
arm_none_eabi_gdb = 'arm-none-eabi-gdb'

def startGdbClient(name, gdbinit, executable, port):

  gdbargs = [arm_none_eabi_gdb,
    '-q', '-batch',
    '-ex', 'target remote localhost:' + port,
    '-ex', 'mon reset 0',
    '-ex', 'load',
    '-ex', 'monitor go',
    '-ex', 'disconnect',
    '-ex', 'quit',
    executable
    ]
  
  if gdbinit != None:
    gdbargs.append('-x')
    gdbargs.append(gdbinit)

  try:
    gdbClient = subprocess.Popen(gdbargs, stdout=fnull, stderr=subprocess.PIPE )
  except FileNotFoundError:
    print('Error: ' + arm_none_eabi_gdb + ' not found')
    print('Check that arm gnu tools are installed and available in your path\n')
    exit(1)

  buf = gdbClient.stderr.read().decode('utf-8')

  if re.search(r'Connection timed out', buf):
    print('Connection timed out.')
    return -1

  lines = buf.split('\n')

  for line in lines:
    line = line.replace('\x00', '')
    line = line.replace('\r', '')
    if re.search(r'^.*(Semihosting|Semi-hosting|SYSRESETREQ).*$', line):
      continue
    print(line)
    if re.search(r'^OK', line):
      return 0
  return 0


def startJlinkGdbServer(name, iface, device, debug_iface, speed, port):
  try:
    gdbServer = subprocess.Popen([name,
      '-select', iface,
      '-device', device,
      '-if',     debug_iface,
      '-speed',  speed,
      '-noir',
      '-port',   port,
      '-singlerun'], stderr = subprocess.PIPE)
  except FileNotFoundError:
    print('Error: ' + name + ' not found')
    print('Check that JLink Utilities are installed and available in your path\n')
    return -1

  buf = gdbServer.stderr.read().decode('utf-8')
  if re.search(r'Could not connect', buf):
    print('Error starting JLink:')
    print(buf)
    return -1

  return 0


if __name__ == "__main__":

  parser = argparse.ArgumentParser(description='JLink Debugger Test Fixture')

  parser.add_argument('-select', default='USB')
  parser.add_argument('-iface', default='SWD', help='SWD or JTAG interface')
  parser.add_argument('-speed', default='auto', help='Interface speed or auto')
  parser.add_argument('-port', default='3333', help='GDBServer port')
  parser.add_argument('-jlinkpath', default=None, help='Path to jlink tools')
  parser.add_argument('-gdbpath', default=None, help='Path to gdb')
  parser.add_argument('executable', help='executable file path')
  parser.add_argument('-gdbinit', help='gdb init script file path')

  required = parser.add_argument_group('required named arguments')
  required.add_argument('-device', help='Microcontroller device. See JLINK Doc', required=True)

  args = parser.parse_args()

  fnull = open(os.devnull, 'w')

  if args.jlinkpath == None:
    if os.name == 'nt':
      jlink_gdbserver = jlink_gdbserver + 'CL.exe'
    else:
      jlink_gdbserver = jlink_gdbserver
    
  if args.gdbpath == None:
    if os.name == 'nt':
      arm_none_eabi_gdb = arm_none_eabi_gdb + '.exe'

  t = threading.Thread(target=startJlinkGdbServer, 
    args = (jlink_gdbserver, args.select, args.device, args.iface, 
        args.speed, args.port))

  t.start()

  # Give some time for the gdbserver to fully startup.
  time.sleep(1)
  
  if not t.isAlive():
    # gdb server died really fast... exit with error
    print("Could not start gdb server. Check log for details.")
    exit( -1 )
  
  # start the client
  rval = startGdbClient(arm_none_eabi_gdb, args.gdbinit, args.executable, args.port)

  exit( rval )

