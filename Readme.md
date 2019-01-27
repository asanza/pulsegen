# Architecture rules:

arch: direct hardware access / hal layer. No os available. The only layer that
      can access hardware directly.

drv: Device drivers. indirect hardware access via hal. depends on arch/os/sys.
os: os services. depends on hal.(arch)
sys: system services. depends on os
lib: common used libraries. Depends on sys