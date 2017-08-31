# Demo App
The demo app is based on Mbed-OS 5. The app offers a Bluetooth LE Service which allows to read characteristics wich provide environmental information.

## Target
Target device is [Nordic nRF52-DK](https://developer.mbed.org/platforms/Nordic-nRF52-DK/) with [X-NUCLEO-IKS01A2](https://developer.mbed.org/components/X-NUCLEO-IKS01A2/) shield

## Build
See [Custom Setup with GNU ARM embedded Toolchain](mbed.md)
* GNU ARM Toolchain
* SRecord Tool (is used in the process to combine Softdevice with user application)
* make (mingw32-make on windows)

## Deploy
* Connect dev board via USB to computer
* Copy & Paste ``.hex`` file from build output to mbed USB drive (JLINK)
* Application is installed and started automatically
