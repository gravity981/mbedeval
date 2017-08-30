# mbedeval
mbed evaluation

# mbed online  compiler
## export project
### Keil
* Need license

### Make ARMGCC
#### Linux
* Install GNU ARM Toolchain: [See here](http://marksolters.com/programming/2016/06/22/arm-toolchain-16-04.html)
* srec_cat missing
  * ``sudo apt-get install srecord``

#### Windows with mingw32 make
* test with mingw toolchain: make (e=2): The  system cannot  find the file specified
  * install GNU ARM Embedded Toolchain: [Link](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
* srec_cat binary not found
  * install SRecord Tools from [here](https://sourceforge.net/projects/srecord/files/srecord-win32/)

#### Integrate in CLion

* TBD edit CMakeLists.txt to include sources and include directories
* TBD deploy binary on target
* TBD debug target

# other
* [Why IDEs are wrong for embedded developers](https://spin.atomicobject.com/2012/09/12/why-ides-are-wrong-for-embedded-developers/)
