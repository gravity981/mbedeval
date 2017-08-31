# mbedeval
This doc is investigates on how to develop applications with
[Mbed OS](https://www.mbed.com/en/platform/mbed-os/)

Further information:
* [How Mbed works](https://developer.mbed.org/handbook/How-mbed-works)
* [ARM Mbed GitHub](https://github.com/ARMmbed)

# mbed online compiler
Within the online compiler you can create new Mbed OS projects based your
[mbed enabled board](https://developer.mbed.org/platforms/) and on template
projects.
On build the online compiler outputs a .hex file which can be downloaded and
copied to the mbed drive of your board (which is connected via USB)

The online IDE lacks some features I think every good IDE should have
* easy navigation in code base
  * find class
  * find file
  * goto definition/declaration
  * find usages/references
* refactoring & code generation
  * variable name
  * class name
  * extract methods
  * generate constructors, implement interface methods
  * method signatures
* code analysis
  * unused #includes, variables
  * auto completion, add missing #includes
* Debugging

# Export mbed online Project
It is possible to export online projects for a couple of toolchains
I want to see which toolchain covers the most points mentioned above.

## Keil
* An IDE from ARM for ARM
  * Flashing & debugging work very well
  * Integrated target configuration
  * Integrated build configuration
* Limited refactoring features
* Bad usability compared to Visual Studio (with Resharper) or IntelliJ

## Eclipse with ARMGCC
TBD

## Alternatives
* Customize a text editor, inspired by: [Why IDEs are wrong for embedded developers](https://spin.atomicobject.com/2012/09/12/why-ides-are-wrong-for-embedded-developers/)
  * E.g. [Atom](https://atom.io/)
* Use different IDEs for different tasks
  * Keil for building and Debugging
    * How to automate/script Keil Build? Mbed CLI Tools?
  * E.g. Visual Studio with [Resharper](https://www.jetbrains.com/resharper-cpp/?fromMenu)
  to develop application
    * How to configure build for simulation on localhost?

### Custom Setup with GNU ARM embedded Toolchain
#### Linux
* Install GNU ARM Toolchain: [See here](http://marksolters.com/programming/2016/06/22/arm-toolchain-16-04.html)
* srec_cat missing
  * ``sudo apt-get install srecord``

#### Windows with mingw32 make
* test with mingw toolchain: make (e=2): The  system cannot  find the file specified
  * install GNU ARM Embedded Toolchain: [Link](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
* srec_cat binary not found
  * install SRecord Tools from [here](https://sourceforge.net/projects/srecord/files/srecord-win32/)

#### Integrate Make-Project in CLion
* TBD edit CMakeLists.txt to use make file for building
* TBD to make CLion analyse Code, in CMakeLists.txt sources and include paths
must be defined
* TBD flash binary on target, is this possible?
  * alternative: script to build .hex and copy it to mbed drive
* TBD debug target, is this possible?

### Mbed CLI Tools
* Try out [Mbed CLI Tools](https://docs.mbed.com/docs/mbed-os-handbook/en/latest/getting_started/blinky_cli/)

### Mbed Design
* [Mbed OS API Reference](https://docs.mbed.com/docs/mbed-os-api-reference/en/latest/)
* to add support for new microcontroller, api's from hal must be implemented
  * [Modular Programming in C ](http://www.embedded.com/design/prototyping-and-development/4023876/Modular-Programming-in-C)
