# Bluetooth Low Energy

## General
 * [GATTOverview](https://www.bluetooth.com/specifications/gatt/generic-attributes-overview)
  * data structure

## Bluetooth LE on Raspberry Pi
[BlueZ](http://www.bluez.org/) offers CLI tools to access BLE devices and debug
their services
* ``sudo hcitool lescan``
* note MAC-address of desired device
* ``gatttool -I -b <MAC-address> -t random``
  * -I is interactive mode
  * -t sets the addr-type [public | random]
  * -b remote ble device address
* ``connect``
* ``characteristics`` show all characteristics
* ``char-desc`` show all characteristic descriptors
* ``char-read-uuid <uuid>`` read value of specific characteristic
* ``char-write-req <handle> <val>`` write value to characteristic
  * val format is hex
  * to enable/disable notifications it is necessary to set the client characteristic configuration descriptor to the correct value. See [here](https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml)
    * uuid for the descriptor can be looked  up with ``char-desc``
* ``disconnect``
* ``exit``

[BluePy](https://github.com/IanHarvey/bluepy) is a Python wrapper for BlueZ

Further information:
* [RPi BLE](http://www.elinux.org/RPi_Bluetooth_LE)

## nRF Connect
* [nRF Connect Mobile](https://play.google.com/store/apps/details?id=no.nordicsemi.android.mcp&hl=de) is a very good app to debug BLE devices
* [nRF Connect for Desktop](https://www.nordicsemi.com/eng/Products/Bluetooth-low-energy/nRF-Connect-for-desktop) requires serial port connection to local dev kit or dongle

## Further information
* [BLE read write Arduino Raspberry Pi](https://lilyhack.wordpress.com/2014/02/03/ble-read-write-arduino-raspberry-pi/)
